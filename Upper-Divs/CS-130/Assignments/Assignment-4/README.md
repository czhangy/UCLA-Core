# Assignment 4

## To-Do

### Configuration

- [x] The server should be made configurable to serve static files on `/static` and echo files on `/echo` (any route should be assignable though)
- [x] The static file handler should serve files from a configurable base directory
- [x] Multiple servlets/request handlers of the same type should be allowed in the configuration

### Request Handler

- [x] Should be able to be given a request object and return the appropriate response
- [x] There should exist a common request handler interface
  - [x] A request handler that handles echo requests should inherit from this
  - [x] A request handler that handles static file requests should inherit from this

### Static Files

- [x] Served files must display properly, meaning the `Content-Type` HTTP header must be set properly
- [x] Supported file extensions must include `.html`, `.jpg`, `.zip`, and `.txt`

### Testing

- [x] Test coverage should be maintained at 90% after changes
- [x] Tests must pass in local Docker image

### Submission

- [x] Ensure the server is running and echoing/serving files in the development environment on Google Cloud
- [x] Submit the IC submission [form](https://docs.google.com/forms/d/e/1FAIpQLSd-Li0TA78Qf7xyURZBXfRELY3GhT63MttTTaH5H7lLu8eHxA/viewform?usp=sf_link)

