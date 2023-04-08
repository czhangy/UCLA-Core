# Assignment 1

## To-Do

- [ ] Environment Setup

  - [ ] Setup WSL2 and initialize an Ubuntu 20.04 distro

  - [ ] Create the `cs130` directory

    ```bash
    mkdir cs130
    ```

  - [ ] Append `nameserver 1.1.1.1` to `/etc/resolv.conf` using `nano`

    ```bash
    sudo nano /etc/resolv.conf
    ```

  - [ ] Download the CS130 tools into `cs130`

    ```bash
    git clone https://code.cs130.org/tools
    ```

  - [ ] Install [Docker](https://docs.docker.com/desktop/install/windows-install/)

  - [ ] Start the dev environment

    ```bash
    tools/env/start.sh -u charleszhang -n -r
    ```

- [ ] Repository Setup

  - [ ] Set up SSH access on [Gerrit](https://code.cs130.org/dashboard/self)
  - [ ] Create a repository named `charleszhang-config-parser`
  - [ ] Set the owner field to `user/CHARLES ZHANG (charleszhang)`

- [ ] Initial Skeleton Code

  - [ ] Clone the repository locally

    ```bash
    git clone ssh://charleszhang@code.cs130.org:29418/charleszhang-config-parser
    ```

  - [ ] Create a branch called `skeleton`

    ```bash
    cd charleszhang-config-parser
    git review -s
    git checkout -b skeleton
    ```

  - [ ] Download and unpack the skeleton code

    ```bash
    curl http://static.cs130.org/src/config-parser.tar.gz | tar -zxv
    ```

  - [ ] Add config files to the project

    ```bash
    ../tools/templates/init.sh
    ```

  - [ ] Stage 12 files for commit

    ```bash
    git add .
    git status
    ```

  - [ ] Commit files to local repository

    ```bash
    git commit -m "Adding initial skeleton code"
    ```

  - [ ] Create a review for the initial commit and delete the `skeleton` branch

    ```bash
    git review -f
    ```

  - [ ] Review the commit from the [Gerrit dashboard](https://code.cs130.org/dashboard/self) and submit the review to push code to the `main` branch

  - [ ] Verify code submission

    ```bash
    git pull
    git log -2
    ```

- [ ] Build Project

  - [ ] Create a new branch `fix_build`

    ```bash
    git checkout -b fix_build
    ```

  - [ ] Remove all references to Boost

  - [ ] Remove the test coverage targets

  - [ ] Address all `# TODO(!)` instructions in `CMakeLists.txt`

    - [ ] Remove all `# TODO(!)` lines

  - [ ] Create a `build` directory at the repository's root

    ```bash
    mkdir build
    cd build
    ```

  - [ ] Run `cmake` to perform an [out-of-source build](https://www.cs130.org/guides/cmake/#out-of-source-builds)

    ```bash
    cmake ..
    make
    ```

  - [ ] Run tests using `make`/`cmake` and directly from the command line

    ```bash
    make test
    cd ../tests && ../build/bin/config_parser_test && cd ..
    ```

  - [ ] Push code to Gerrit and review it

    ```bash
    git add .
    git status
    git commit -m "Fixed broken skeleton code"
    git review -f
    ```

- [ ] Unit Testing

  - [ ] Get familiar with the config format for unit tests [here](http://nginx.org/en/docs/beginners_guide.html#conf_structure) and [here](https://docs.nginx.com/nginx/admin-guide/basic-functionality/managing-configuration-files/#)

  - [ ] Create a new branch `unit_tests`

    ```bash
    git checkout -b "unit_tests"
    ```

  - [ ] Create a [test fixture](https://github.com/google/googletest/blob/main/docs/primer.md#test-fixtures-using-the-same-data-configuration-for-multiple-tests-same-data-multiple-tests) for the parser

  - [ ] Write more unit tests for the config parser in `config_parser_test.cc`

    - [ ] Fix identified bugs

  - [ ] Push code to Gerrit for review

    ```bash
    git add .
    git status
    git commit -m "Added unit tests"
    git review -f
    ```

- [ ] Code Reviews

  - [ ] Find a partner for [code reviews](https://docs.google.com/spreadsheets/d/1bQqnl7h12Dw64KHyZDEQhNp5My3OU16YB0d45lhSM4k/edit#gid=0)
  - [ ] Learn how to [respond to reviews](https://www.cs130.org/guides/gerrit/#responding-to-reviews)
  - [ ] Submit at least 3 changes for review
  - [ ] Respond to a comment with new changes on at least 1 review
  - [ ] Submit code to the `main` branch

- [ ] Submission

  - [ ] Ensure all code is in the `main` branch
  - [ ] Submit assignment to [form](https://docs.google.com/forms/d/e/1FAIpQLSdZuTeUOab1IcXsMHcqeyORBlVIDN88h6rabpCBWJclBVhKAg/viewform)

