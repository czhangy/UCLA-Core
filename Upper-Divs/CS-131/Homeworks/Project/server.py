#!/usr/bin/python

# Example Commands
# IAMAT kiwi.cs.ucla.edu +34.068930-118.445127 1614209128.918963997

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
                "Juzang": ["Riley", "Campell", "Bernard"],
                "Campbell": ["Juzang", "Bernard"],
                "Bernard": ["Jaquez", "Juzang", "Campbell"]}

# Server Class
class Server:
    def __init__(self, server_name, server_port, server_ip):
        # Get data members
        self.name = server_name
        self.port = server_port
        self.ip = server_ip
        self.client_data = dict()
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
            # Handle empty input edge case
            if len(ops) == 0:
                continue
            # Handle IAMAT requests --> ops[1] = domain, ops[2] = lat/long, ops[3] = timestamp
            elif ops[0] == "IAMAT":
                reply = self.handle_IAMAT(ops)
            # Handle WHATSAT requests
            elif ops[0] == "WHATSAT":
                reply = self.handle_WHATSAT(ops)
            # Handle AT requests (propagations)
            elif ops[0] == "AT":
                reply = self.handle_AT(ops)
            # Invalid command
            else:
                reply = f'? {cmd}'
            # Log and write the reply
            logging.info(f' {str(datetime.now())}: {self.name} replied with: "{reply}"')
            reply = reply + "\n"
            writer.write(reply.encode())
            await writer.drain()
        # Log client disconnection
        logging.info(f' {str(datetime.now())}: Client disconnected')
        writer.close()

    # Handle potential IAMAT commands
    def handle_IAMAT(self, cmd):
        # Function to check IAMAT syntax
        def check_IAMAT(cmd):
            if len(cmd) != 4:
                return False
            return True
        # Check syntax of IAMAT command
        if check_IAMAT(cmd):
            # Calculate timestamp difference
            time_diff = time.time() - float(cmd[3])
            if time_diff > 0:
                time_diff = "+" + str(time_diff)
            # Reply with AT
            reply = f'AT {self.name} {time_diff} {cmd[1]} {cmd[2]} {cmd[3]}'
            self.client_data[cmd[1]] = reply
        # Invalid command
        else:
            reply = f'? + {cmd}'
        return reply

    # Handle potential WHATSAT commands
    def handle_WHATSAT(self, cmd):
        return ""

    # Handle potential AT commands
    def handle_AT(self, cmd):
        return ""

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
        logging.basicConfig(filename=f'./{args.server_name}_log.txt', filemode="+w", level=logging.INFO)
        # Init server using name, corresponding port, and local IP
        s = Server(args.server_name, server_ports[args.server_name], '127.0.0.1')
        asyncio.run(s.manage_server())


# Boilerplate
if __name__ == '__main__':
    main()
