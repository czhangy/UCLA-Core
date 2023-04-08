# Assignment 1

## To-Do

- [x] Environment Setup

  - [x] Setup [WSL2](https://learn.microsoft.com/en-us/windows/wsl/install) and initialize an Ubuntu 20.04 distro

  - [x] Configure WSL to mount drives at `/` instead of `/mnt`

    ```bash
    sudo tee -a /etc/wsl.conf << EOF
    [automount]
    root = /
    options = "metadata"
    EOF
    ```

  - [x] Create the `cs130` directory

    ```bash
    mkdir cs130
    cd cs130
    ```

  - [x] Append `nameserver 1.1.1.1` to `/etc/resolv.conf` using `nano`

    ```bash
    sudo nano /etc/resolv.conf
    ```

  - [x] Download the CS130 tools into `cs130`

    ```bash
    git clone https://code.cs130.org/tools
    ```

  - [x] Install [Docker](https://docs.docker.com/desktop/install/windows-install/) and run it

  - [x] Verify Docker is installed properly

    ```bash
    docker run -it hello-world
    ```

  - [x] Start the dev environment

    ```bash
    tools/env/start.sh -u charleszhang -n -r
    ```

  - [x] Append `nameserver 1.1.1.1` to `/etc/resolv.conf` using `nano` in the dev environment

  - [x] Set new username and email in git config

    ```bash
    git config --global user.name "charleszhang"
    git config --global user.email "charleszhang@g.ucla.edu"
    ```

- [x] Repository Setup

  - [x] Set up SSH access on [Gerrit](https://code.cs130.org/dashboard/self)
  - [x] Create a repository named `charleszhang-config-parser`
  - [x] Set the owner field to `user/CHARLES ZHANG (charleszhang)`

- [x] Initial Skeleton Code

  - [x] Clone the repository locally

    ```bash
    git clone ssh://charleszhang@code.cs130.org:29418/charleszhang-config-parser
    ```

  - [x] Create a branch called `skeleton`

    ```bash
    cd charleszhang-config-parser
    git checkout -b skeleton
    ```

  - [x] Download and unpack the skeleton code

    ```bash
    curl http://static.cs130.org/src/config-parser.tar.gz | tar -zxv
    ```

  - [x] Add config files to the project

    ```bash
    ../tools/templates/init.sh
    ```

  - [x] Stage files for commit

    ```bash
    git add .
    git status
    ```

  - [x] Commit files to local repository (ensure 12 files are committed)

    ```bash
    git commit -m "Adding initial skeleton code"
    ```

  - [x] Create a review for the initial commit and delete the `skeleton` branch

    ```bash
    git review -f
    ```

  - [x] Review the commit from the [Gerrit dashboard](https://code.cs130.org/dashboard/self) and submit the review to push code to the `main` branch

  - [x] Verify code submission

    ```bash
    git pull
    git log -2
    ```

- [x] Build Project

  - [x] Create a new branch `fix_build`

    ```bash
    git checkout -b fix_build
    ```

  - [x] Open the project in VSCode

    ```bash
    code .
    ```

  - [x] Remove all references to Boost from `CMakeLists.txt`

  - [x] Remove the test coverage targets from `CMakeLists.txt`

  - [x] Address all `# TODO(!)` instructions in `CMakeLists.txt`

    - [x] [Investigate](https://www.cs130.org/guides/cmake/#important-functions) `add_library`, `add_executable`, `target_link_libraries`, and `gtest_discover_tests`
    - [x] Create a library with `config_parser.cc` code
    - [x] Create an executable with `config_parser_main.cc` code and link it to the library
    - [x] Create an executable with `config_parser_test.cc` code and link it to the library
    - [x] Update test discovery
    - [x] Remove all `# TODO(!)` lines

  - [x] Create a `build` directory at the repository's root

    ```bash
    mkdir build
    cd build
    ```

  - [x] Run `cmake` to perform an [out-of-source build](https://www.cs130.org/guides/cmake/#out-of-source-builds)

    ```bash
    cmake ..
    make
    ```

  - [x] Run tests using `make`/`cmake` and directly from the command line

    ```bash
    make test
    cd ../tests && ../build/bin/config_parser_test && cd ..
    ```

  - [x] Push code to Gerrit and review it

    ```bash
    git add .
    git status
    git commit -m "Fixed broken skeleton code"
    git review -f
    ```

  - [x] Update the `main` branch of your local repository

    ```bash
    git pull
    ```

- [ ] Unit Testing

  - [x] Get familiar with the config format [here](http://nginx.org/en/docs/beginners_guide.html#conf_structure) and [here](https://docs.nginx.com/nginx/admin-guide/basic-functionality/managing-configuration-files/#)

  - [x] Create a new branch `unit_tests`

    ```bash
    git checkout -b "unit_tests"
    ```

  - [x] Create a [test fixture](https://github.com/google/googletest/blob/main/docs/primer.md#test-fixtures-using-the-same-data-configuration-for-multiple-tests-same-data-multiple-tests) for the parser

  - [ ] Write more unit tests for the config parser in `config_parser_test.cc`

  - [ ] Fix bugs identified by the unit tests

  - [ ] Push code to Gerrit for review

    ```bash
    git add .
    git status
    git commit -m "Added unit tests"
    git review -f
    ```

- [ ] Code Reviews

  - [x] Find a partner for [code reviews](https://docs.google.com/spreadsheets/d/1bQqnl7h12Dw64KHyZDEQhNp5My3OU16YB0d45lhSM4k/edit#gid=0)
  - [ ] Learn how to [respond to reviews](https://www.cs130.org/guides/gerrit/#responding-to-reviews)
  - [ ] Submit at least 3 changes for review
  - [ ] Respond to a comment with new changes on at least 1 review
  - [ ] Submit code to the `main` branch

- [ ] Submission

  - [ ] Ensure all code is in the `main` branch
  - [ ] Submit assignment to [form](https://docs.google.com/forms/d/e/1FAIpQLSdZuTeUOab1IcXsMHcqeyORBlVIDN88h6rabpCBWJclBVhKAg/viewform)

