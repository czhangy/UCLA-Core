# Assignment 8

## To-Do

### CRUD Handler

- [x] Fix the CRUD handler

### Multithreading

- [x] Implement a sleep handler to force a thread to sleep for `x` seconds
- [x] Implement a thread pool to allow requests to be run in parallel
- [x] Protect the CRUD API using mutexes to prevent race conditions

### Google Cloud Deploy

- [x] Create a persistent disk to allow data passed through the CRUD API to persist across instances
- [x] Extract response metrics from logs using the magic string `[ResponseMetrics]`
- [x] Create an uptime check using the health handler
- [x] Create a dashboard showing server metrics

### Product Requirements Document

- [x] Write the PRD according to the example document

### General Health

- [x] Implement a mock logger for unit testing purposes
- [x] Factor code out of `main()` into a new object for testing
- [x] Reorganize unit test structure
- [x] Improve code coverage

### Submission

- [x] Make sure all changes are pushed to `main` and approved
- [x] Submit the IC response [form](https://docs.google.com/forms/d/e/1FAIpQLSdp7Tc1g7k9dxmAnsiasOj4TftN2OJqDzSPRlhyfGvWrrKryQ/viewform)