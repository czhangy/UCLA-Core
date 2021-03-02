# Proxy Herd with `asyncio`

## Goal

**Use Python 3.9.2's `asyncio` library to write a parallelizable proxy for the Google Places API**

## Assigned Ports

```json
15835
15836
15837
15838
15839
```

## Coding

- 5 servers (Riley, Jaquez, Juzang, Campbell, and Bernard) that talk bidirectionally
  - Riley talks with Jaquez and Juzang
  - Bernard talks with everyone but Riley
  - Juzang talks with Campbell
- Servers accept TCP connections from clients with IPs and DNS names
- Communicate location:
  - Client sends location with: `IAMAT [CLIENT_ID] [ISO 6709 LATITUDE_LONGITUDE] [POSIX_TIMESTAMP]`
    - `[CLIENT_ID]` may be any string of non-whitespace characters
  - Servers respond to location with: `AT [SERVER_ID] [TIME_DIFF] [IAMAT_FIELDS]`
- Communicate place:
  - Clients can query for information with: `WHATSAT [ANOTHER_CLIENT_ID] [RADIUS] [AMNT_OF_INFO]`
    - `[RADIUS]` < 50km
    - `[AMNT_OF_INFO]` < 20
  - Servers respond with: `AT [SERVER_ID] [TIME_DIFF] [IAMAT_FIELDS] [JSON_RESPONSE]`
    - The Google Places API gives the response in JSON format, simply remove duplicate newlines
- Servers respond to invalid commands with: `? [INVALID_COMMAND]`
- Servers communicate using AT messages to propagate location updates
  - Only propagate locations, not place information
- Servers should continue to operate if their neighboring servers go down
- Servers log I/O into a file, design the format
- Servers only handle one request per connection
- Messages are ended by EOF, can be handled by `reader.read`
- Server must manually create HTTP GET requests using the `aiohttp` library
  - `asyncio` only supports TCP and SSL protocols
- Main file names `server.py`
  - Takes one command line argument: `python3 server.py [SERVER_ID]`
    - Each command launches 1 of the servers - 5 needed to launch all servers

## Testing

- Use `telnet` or `nc` to test the server
- `nc -l [PORT]` starts a server on your machine, using port `[PORT]`
  - This can then be connected to in a separate window using: `nc 127.0.0.1 [PORT]`
- `screen` can be used to multiplex several terminal sessions
  - `Ctrl + A C` creates a new window
  - `Ctrl + A [WINDOW_NUMBER]` switches windows
- Postman can be used to test HTTP requests without coding

## Report

- Make a recommendation pro or con and justify it
- Directly address Python's type checking, memory management, and multithreading
  - Compare to Java approach
- Compare overall approach of `asyncio` to Node.js
- Focus on:
  - How easy is it to write asyncio-based programs that run and exploit server herds?
  - What are the performance implications of using asyncio?
  - How important is it to rely on asyncio features of Python 3.9 or later, such as `asyncio.run` and `python -m asyncio`, or is it easy to get by with older versions of Python?
- LaTeX styling
- 5 pages maximum

## Submission

- Source code in gzipped file named `project.tgz`
  - [ ] Create servers/address command line
  - [ ] Implement `IAMAT` command
  - [ ] Implement a flooding algorithm
  - [ ] Implement `WHATSAT` command
  - [ ] Perform testing
- Report in file named `report.pdf`
  - [ ] Create template
  - [ ] Address pros and cons
  - [ ] Problems run into
  - [ ] Address Python vs. Java
  - [ ] Address `asyncio` vs. Node.js
  - [ ] Address dependance on Python 3.9+ features

## Relevant Links

- **[`asyncio` source code](https://github.com/python/cpython/tree/master/Lib/asyncio)**
- **[`asyncio` documentation](https://docs.python.org/3/library/asyncio.html)**
- **[`aiohttp` documentation](https://aiohttp.readthedocs.io/en/stable/)**
- **[Flooding algorithm](http://en.wikipedia.org/wiki/Flooding_%28computer_networking%29)**
- **[Google Places API key](https://console.developers.google.com/flows/enableapi?apiid=places_backend&keyType=SERVER_SIDE&reusekey=true)**
- **[Google Places Place Search Documentation](https://developers.google.com/maps/documentation/places/web-service/search)**
- **[Postman](https://www.postman.com/)**
- **[USENIX style templates](https://www.usenix.org/conferences/author-resources/paper-templates)**
