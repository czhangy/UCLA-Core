# Example Commands
# IAMAT kiwi.cs.ucla.edu +34.068930-118.445127 1614209128.918963997
# WHATSAT kiwi.cs.ucla.edu 10 5

import aiohttp
import argparse
import asyncio
from datetime import datetime
import json
import logging
import sys
import time

# Global Variables
# Valid server names
server_names = ["Riley", "Jaquez", "Juzang", "Campbell", "Bernard"]

# Dict to map from server name --> hard-coded port
server_ports = {"Riley": 15835, "Jaquez": 15836,
                "Juzang": 15837, "Campbell": 15838, "Bernard": 15839}

# Dict to map from server name --> neighboring servers
server_comms = {"Riley": ["Jaquez", "Juzang"],
                "Jaquez": ["Riley", "Bernard"],
                "Juzang": ["Riley", "Campbell", "Bernard"],
                "Campbell": ["Juzang", "Bernard"],
                "Bernard": ["Jaquez", "Juzang", "Campbell"]}

# API Key
KEY = 1 # Insert API key here

# Server Class
class Server:
    def __init__(self, server_name, server_port, server_ip):
        # Get data members
        self.name = server_name
        self.port = server_port
        self.ip = server_ip
        self.domain_info = dict()
        # Log server start-up
        logging.info(f' {str(datetime.now())}: {self.name} constructed')

    # Server initialization and closing
    async def manage_server(self):
        # Start the server
        s = await asyncio.start_server(self.get_commands, self.ip, self.port)
        logging.info(f' {str(datetime.now())}: {self.name} initialized')
        # Accept connections until cancelled
        await s.serve_forever()
        # Close the server
        s.close()
        logging.info(f' {str(datetime.now())}: {self.name} closed')

    # Handle commands
    async def get_commands(self, reader, writer):
        # While the buffer is empty, loop
        while not reader.at_eof():
            # Get command
            temp = await reader.readline()
            cmd = temp.decode().rstrip()
            # Log received command
            logging.info(f' {str(datetime.now())}: {self.name} received command: "{cmd}"')
            # Prepare command for processing
            ops = cmd.split()
            reply = None
            # Handle empty input edge case
            if len(ops) == 0:
                continue
            # Handle IAMAT requests
            elif ops[0] == "IAMAT":
                reply = await self.handle_IAMAT(ops)
            # Handle WHATSAT requests
            elif ops[0] == "WHATSAT":
                reply = await self.handle_WHATSAT(ops)
            # Handle AT requests (propagations)
            elif ops[0] == "AT":
                reply = await self.handle_AT(ops)
            # Invalid command
            else:
                reply = f'? {cmd}'
            # Log and write the reply, if it exists
            if (reply != None):
                logging.info(f' {str(datetime.now())}: {self.name} replied with: "{reply}"')
                reply = reply + "\n"
                writer.write(reply.encode())
                await writer.drain()
        # Log client disconnection
        logging.info(f' {str(datetime.now())}: Client disconnected')
        writer.close()

    # Check if a string is a valid number
    def is_num(self, x):
        try:
            float(x)
            return True
        except:
            return False

    # Handle potential IAMAT commands --> cmd[1] = domain, cmd[2] = lat/long, cmd[3] = timestamp
    async def handle_IAMAT(self, cmd):
        # Function to check IAMAT syntax
        def check_IAMAT(cmd):
            # Check for proper length and valid timestamp
            if len(cmd) != 4 or not self.is_num(cmd[3]):
                return False
            temp = cmd[2].replace('+', '-')
            coords = list(filter(None, temp.split('-')))
            # Check for proper coordinates
            if not self.is_num(coords[0]) or not self.is_num(coords[1]):
                return False
            return True
        # Check syntax of IAMAT command
        if check_IAMAT(cmd):
            # Calculate and format timestamp difference
            time_diff = time.time() - float(cmd[3])
            if time_diff > 0:
                time_diff = "+" + str(time_diff)
            # Reply with AT
            reply = f'AT {self.name} {time_diff} {cmd[1]} {cmd[2]} {cmd[3]}'
            # Save domain information
            self.domain_info[cmd[1]] = reply
            # Propagate to neighboring servers
            await self.flooding_algo(reply)
        # Invalid command
        else:
            reply = f'? + {" ".join(cmd)}'
        return reply

    # Handle potential WHATSAT commands --> cmd[1] = domain, cmd[2] = radius, cmd[3] = info amnt
    async def handle_WHATSAT(self, cmd):
        # Function to check WHATSAT syntax
        def check_WHATSAT(cmd):
            # Check if the domain exists
            if cmd[1] not in self.domain_info:
                return False
            # Check if radius and info amnt are numbers
            if not self.is_num(cmd[2]) or not self.is_num(cmd[3]):
                return False
            # Check if radius and info amnt are within bounds
            if int(cmd[2]) < 0 or int(cmd[2]) > 50 or int(cmd[3]) < 0 or int(cmd[3]) > 20:
                return False
            return True
        if check_WHATSAT(cmd):
            # Get JSON data from Google Places
            json_data = await self.access_api(self.domain_info[cmd[1]].split()[-2], cmd[2], int(cmd[3]))
            reply = '{}\n{}\n\n'.format(self.domain_info[cmd[1]], str(json_data).rstrip('\n'))
        else:
            reply = f'? + {" ".join(cmd)}'
        return reply

    # Handle potential AT commands --> cmd[1] = origin server, cmd[2] = time diff, cmd[3] = domain, cmd[4] = lat/long, cmd[5] = timestamp
    async def handle_AT(self, cmd):
        # Function to check AT syntax
        def check_AT(cmd):
            # Check length and valid origin server name
            if len(cmd) != 6 or cmd[1] not in server_names:
                return False
            # Check valid timestamp
            temp = cmd[2].replace('+', '-')
            if not self.is_num(temp):
                return False
            # Check IAMAT formatting
            temp = cmd[4].replace('+', '-')
            coords = list(filter(None, temp.split('-')))
            if not self.is_num(cmd[5]) or not self.is_num(coords[0]) or not self.is_num(coords[1]):
                return False
            return True
        # Check command syntax
        if check_AT(cmd):
            # Shut down repeat propagations
            if cmd[3] in self.domain_info and float(self.domain_info[cmd[3]].split()[-1]) >= float(cmd[5]):
                logging.info(f' {str(datetime.now())}: Message from {cmd[1]} already received')
                reply = None
            else:
                # Log propagation
                logging.info(f' {str(datetime.now())}: Received "{" ".join(cmd)}" from {cmd[1]}')
                # Propagate to neighbors
                await self.flooding_algo(" ".join(cmd))
                reply = " ".join(cmd)
                # Update current server's domain info
                self.domain_info[cmd[3]] = reply
        # Invalid command
        else:
            reply = f'? + {" ".join(cmd)}'
        return reply

    # Flooding algorithm
    async def flooding_algo(self, cmd):
        for server in server_comms[self.name]:
            try:
                # Open connection to other server and send message
                _, writer = await asyncio.open_connection('127.0.0.1', server_ports[server])
                writer.write(cmd.encode())
                await writer.drain()
                # Log propagated message
                logging.info(f' {str(datetime.now())}: {self.name} propagated "{cmd}" to {server}')
                writer.close()
                await writer.wait_closed()
                # Log closed connection
                logging.info(f' {str(datetime.now())}: {self.name} closed connection to {server}')
            except:
                # Log failed connection
                logging.info(f' {str(datetime.now())}: {self.name} failed to connect to {server}')

    # Get JSON data for WHATSAT command
    async def access_api(self, coords_str, radius, info_amnt):
        # Use HTTP
        async with aiohttp.ClientSession() as client:
            # Format long/lat for API access
            ind = max(map(coords_str.find, '+-'))
            coords = f'{coords_str[0:ind]},{coords_str[ind:]}'
            # Log API access attempt
            logging.info(f' {str(datetime.now())}: {self.name} accessing API for location {coords}')
            # Build URL using API key and parameters
            url = f'https://maps.googleapis.com/maps/api/place/nearbysearch/json?location={coords}&radius={radius}&key={KEY}'
            # Fetch data
            json_data = await self.fetch(client, url)
            # Log data retrieval
            logging.info(f' {str(datetime.now())}: {self.name} retrieved data for location {coords} from API')
            # Get Python object
            json_dict = json.loads(json_data)
            # Check if data amount overloads the max bound of the WHATSAT command
            if (len(json_dict["results"]) > info_amnt):
                # Truncate
                json_dict["results"] = json_dict["results"][0:info_amnt]
                return json.dumps(json_dict, indent = 4, sort_keys = True)
            # Data was fine, return original JSON result
            return json_data

    # Access Google Places API
    async def fetch(self, client, url):
        async with client.get(url) as req:
            return await req.text()

# Starting point
def main():
    # Use argparse to read through command line input
    parser = argparse.ArgumentParser(description='Parse through the input command')
    parser.add_argument('server_name', type=str)
    args = parser.parse_args()
    if not args.server_name in server_names:
        # Fail for invalid name
        print(f'Exiting: {args.server_name} is not a valid server name')
        sys.exit()
    else:
        # Init logs
        logging.basicConfig(filename=f'./{args.server_name}_log.txt', level=logging.INFO)
        # Init server using name, corresponding port, and local IP
        s = Server(args.server_name, server_ports[args.server_name], '127.0.0.1')
        try:
            asyncio.run(s.manage_server())
        except:
            logging.info(f' {str(datetime.now())}: {args.server_name} closed')
            sys.exit()

# Boilerplate
if __name__ == '__main__':
    main()
