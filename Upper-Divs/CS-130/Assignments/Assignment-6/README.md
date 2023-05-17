# Assignment #6

## To-Do

### API Refactor

- [x] Config file
  - [x] The name of the handler should be moved into the main declaration (outside the block directive)
  - [x] `ConfigReader` functionality should be moved to `NginxConfig`
  - [x] Trailing backslashes should be ignored
- [x] Request handler interface
  - [x] `Request` and `Response` objects should be replaced by their `boost` equivalents
  - [x] The name of the main function in `RequestHandler` should be `HandleRequest`
  - [x] Request handlers should have access to the full path of the requested URL and the matching route location path
- [x] Request handlers
  - [x] Request handlers should be created by request handler factories
  - [x] Request handler factories should be assigned by the dispatch mechanism
  - [x] Request handler factories should be responsible for parsing the Nginx config
  - [x] Request handlers should have short lifetimes, synchronized to an incoming request
- [x] Dispatch mechanism
  - [x] `Dispatcher` should use longest prefix matching to match an incoming request to a specific handler factory
  - [x] `HandlerManager` functionality should be moved into `Dispatcher`

### 404 Handler

- [x] A new handler should be registered to serve at `/`
- [x] This handler should send a 404 Not Found response using the common API

### Documentation

- [x] A `README.md` should be created for contributor documentation
- [x] The source code's layout should be specified
- [x] A detailed walkthrough of building, testing, and running the code should be provided
- [x] Information on how to add a request handler should be written
  - [x] Well-documented example of an existing handler
  - [x] Well-documented header files

### Submission

- [x] Make sure all changes are pushed to `main` and approved
- [x] Submit the IC response [form](https://docs.google.com/forms/d/e/1FAIpQLSfi76XbVzEuoCFGhBd92UBUNBEcV6rOyYvr8MC7eh-BA37Vlg/viewform)