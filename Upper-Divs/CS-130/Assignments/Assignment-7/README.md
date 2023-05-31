# Assignment 7

## To-Do

### Setting Up

- [x] Find the team we're assigned to [here](https://docs.google.com/spreadsheets/d/1QfkuC2QmX-MQEiA8Z0n2xWVNImrAGRkiE44Oi0FhJTw/edit)
- [x] Clone their repository

### CRUD Handler

- [x] `CRUDHandler()`
  - [x] Construct the data path if it doesn't already exist
- [x] `HandleRequest()`
  - [x] Determine if a `GET` request is a `GET`request or a `LIST` request
- [x] `GET` request
  - [x] Fetch file contents if the path exists
  - [x] Return 404 if it doesn't exist
- [x] `LIST` request
  - [x] Fetch list of valid IDs for a requested Entity
  - [x] Return 404 if the entity doesn't exist

### Filesystem

- [x] Define a `Filesystem` abstract base class
- [x] Implement a `BoostFilesystem` object
  - [x] Should make use `Boost::filesystem` methods to implement functions
  - [x] Should be used in actual server code
- [x] Implement a `MockFilesystem` object
  - [x] Should make use of `std::unordered_map` to implement functions

### Testing

- [x] Write unit tests using `MockFilesystem`
- [x] Write integration tests for `GET` and `LIST` methods

### Submission

- [x] Make sure all changes are pushed to `main` and approved
- [x] Submit the IC response [form](https://docs.google.com/forms/d/e/1FAIpQLScJqj6QsrYRM7XTlnNuaZBBk6YhyKnJWxlJVSIvsPT3rbq8Kw/viewform)