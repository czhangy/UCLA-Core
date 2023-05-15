# Assignment 2 assessment for runtime-terror

## Results

| Score |            Area             |                           Criteria                           | Notes |
| :---: | :-------------------------: | :----------------------------------------------------------: | :---: |
| 30/30 | Project Health / Unit tests | Test pass rate (in build at submitted commit, either in local Docker build or manual build if CMake/Docker is broken) |       |
|  4/4  |  Assignment / Refactoring   | At least 4 .cc files created (e.g. config_parser, session, server, server_main) |       |
|  3/3  |  Assignment / Refactoring   | At least 3 .h files created (e.g. config_parser, session, server) |       |
|  3/3  |  Assignment / Refactoring   | Test code and data in separate directory from src (e.g. tests/) |       |
|  3/3  |   Assignment / Dockerfile   |       Dockerfile has expected updates (TODOs followed)       |       |
|  2/2  |   Assignment / Dockerfile   |         Hygiene: TODOs were removed / not checked in         |       |
|  3/3  |     Assignment / Config     |          Config file can be found in report or repo          |       |
|  2/2  |     Assignment / Config     |                  Config file contains port                   |       |
| 15/15 |     Assignment / Build      | Server builds without failure in local Docker (or manually at last commit) |       |
| 10/10 |     Assignment / Build      | Server built successfully on Cloud Build (build image found) |       |
|  5/5  |   Assignment / Deployment   | Instance was created on Cloud with external IP (ignore status) |       |
| 20/20 | Assignment / Functionality  | curl_root test passes in local build server test or Cloud build server test (or almost passes: allow single newline error in diff) |       |
|  -2   |    Assignment Penalties     | Response does not have terminating newline, or other whitespace error in diff |       |
|  2/2  |        Extra Credit         |      20 or more unit tests (check "Unit test results:")      |       |

## Total team score: 100 / 100