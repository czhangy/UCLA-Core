# Assignment 6 assessment for runtime-terror

## Results

| Score |                       Area                        |                           Criteria                           |             Notes              |
| :---: | :-----------------------------------------------: | :----------------------------------------------------------: | :----------------------------: |
| 25/25 |            Project Health / Unit tests            |                 Test coverage (lines) > 80%                  |                                |
| 15/15 |         Project Health / Continuous build         |                   Build passing rate > 80%                   |                                |
|  2/2  |            Project Health / Deployment            |      Compute instance in RUNNING state with external IP      |                                |
|  3/3  |            Project Health / Deployment            | Docker container running on at least 1 Compute instance for longer than 5 mins |                                |
|  2/2  |          Assignment / Common API Config           |                 Has location-major structure                 |                                |
|  2/2  |          Assignment / Common API Config           |                    Uses location keyword                     |                                |
|  2/2  |          Assignment / Common API Config           |                 Has named handler arguments                  |                                |
|  2/2  |          Assignment / Common API Config           |              Supports relative filesystem paths              |                                |
|  0/2  |          Assignment / Common API Config           |            Ignores trailing slashes on URL paths             |                                |
|  2/2  | Assignment / Common API Request Handler Factories | Uses RequestHandlerFactories to create per-request handlers  |                                |
|  1/2  | Assignment / Common API Request Handler Factories | Uses RequestHandlerFactories to pass arguments as NginxConfig to handler constructor | not passing config to handlers |
|  2/2  | Assignment / Common API Request Handler Factories | Server has static knowledge of all RequestHandlerFactories and creates at server startup |                                |
|  2/2  | Assignment / Common API Request Handler Interface |       Has a single handle_request method (or similar)        |                                |
|  2/2  | Assignment / Common API Request Handler Interface |         handle_request returns non-void info/status          |                                |
|  2/2  | Assignment / Common API Request Handler Interface |       handle_request takes boost::beast::http::request       |                                |
|  2/2  | Assignment / Common API Request Handler Interface | handle_request writes boost::beast::http::response as out-param |                                |
|  2/2  |        Assignment / Common API Dispatcher         |        Has a map of paths to RequestHandlerFactories         |                                |
|  2/2  |        Assignment / Common API Dispatcher         |  Routes to matching handler through longest matching prefix  |                                |
|  1/2  |        Assignment / Common API Dispatcher         | RequestHandler is given full requested URL and location path from config |     only passing location      |
| 15/15 |      Assignment / Contributor Documentation       | Documentation provides sufficient context to new contributor to write a request handler |                                |
| 10/10 |             Assignment / 404 Handler              |           Correctly returns 404 for unmapped paths           |                                |
|  5/5  |                   Extra Credit                    |      Went above and beyond in contributor documentation      |                                |

## Total team score: 101 / 100