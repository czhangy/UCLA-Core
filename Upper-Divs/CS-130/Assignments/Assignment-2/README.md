# Assignment 2

## To-Do

### Team Resource Setup

- [x] Get in contact with the team
- [x] Assign a TL for the assignment
- [x] Choose a team name
- [x] Set up Gerrit for the team
  - [x] Create a [group](https://www.cs130.org/guides/gerrit/#group-setup) for the team in Gerrit and make the group visible to all registered users in Group Options
  - [x] Create a [repository](https://www.cs130.org/guides/gerrit/#creating-a-git-repository) for the team in Gerrit and set the owner to the team's group
- [x] Make a new project in [GCP](https://console.cloud.google.com/projectcreate?organizationId=461747480190) with your @g.ucla.edu account
  - [x] Enter the team name as the project name and ensure the billing account matches the name of your recently created account
  - [x] Set the organization to `cs130.org`, the location to 2023, and create the project
  - [x] Grant access to your project to all team members as "New principals" with the "Owner" role through the IAM & Admin section of the project dashboard
  - [x] [Initialize](https://www.cs130.org/guides/gcloud/#initialization) `gcloud`

### Skeleton Code

- [x] Upload skeleton code to the team repository

  ```bash
  git clone ssh://charleszhang@code.cs130.org:29418/${REPO}
  cd ${REPO}
  git checkout -b skeleton
  git review -s
  curl http://static.cs130.org/src/boost-server.tar.gz | tar -zxv
  ```

- [x] Generate config files in the project repo

  ```bash
  ../tools/templates/init.sh
  ```

- [x] Edit `CMakeLists.txt`

  - [ ] Compile `server_main.cc` and link it with `Boost::system`
  - [ ] Comment out the test executable, the `gtest_discover_tests` rule, and the code coverage rule

- [x] Compile the server

  ```bash
  mkdir build
  cd build
  cmake ..
  make
  ```

- [x] Launch the server with a test port

  ```bash
  bin/server 8080
  ```

- [x] Use `netcat` in a separate terminal to check for a server response

  ```bash
  nc localhost 8080
  ```

- [x] Send this code for review on Gerrit

### Echoing Web Server

- [x] Refactor `server_main.cc` into a separate source and header file for each class

- [x] Send the refactored code for review on Gerrit

- [ ] Write a server that listens on a configurable port and responds to HTTP 1.1 requests by echoing the request back to the client

  - [ ] Reference the HTTP/1.1 spec for [request](https://www.w3.org/Protocols/rfc2616/rfc2616-sec5.html#sec5) and [response](https://www.w3.org/Protocols/rfc2616/rfc2616-sec6.html#sec6)

  - [ ] Detect when the request is complete

  - [ ] Send an HTTP 200 response code

  - [ ] Set the content type to `text/plain`

  - [ ] Send the request in the body of the response

  - [x] Use the config parser code from Assignment 1 and allow the config file to configure a port number

    ```bash
    bin/webserver config_file
    ```

- [ ] Send the server code for review on Gerrit

### Docker Container

- [ ] Address all the `TODO(!)` comments in `docker/Dockerfile`

  - [ ] In the deploy stage, add command-line parameters (server config filename) for the `ENTRYPOINT` [binary](https://docs.docker.com/engine/reference/builder/#entrypoint) with the `CMD` [statement](https://docs.docker.com/engine/reference/builder/#cmd)
  - [ ] [`COPY`](https://docs.docker.com/engine/reference/builder/#copy) the config file from the `builder` stage, so it's accessible in the `deploy` stage, referencing the [docs](https://docs.docker.com/develop/develop-images/multistage-build/)

- [ ] [Build and run](https://www.cs130.org/guides/docker/#example-usage) the server with Docker using the edited `Dockerfile`, building and tagging the `:base` image before `builder`

  - [ ] Map the server's port to a port on `127.0.0.1`

- [ ] Shut down the Docker container

  ```bash
  docker container stop
  ```

- [ ] Send the `Dockerfile` for review on Gerrit

### GCP Deployment

- [ ] Create a new config file using port 80 for the Docker container

- [ ] [Build](https://www.cs130.org/guides/gcloud/#building-a-container) a Docker container on GCP

- [ ] [See](https://console.cloud.google.com/cloud-build/builds) the results of your build

  - [ ] Click on **Build ID** in the **Build history** table to see the **Build details**
  - [ ] View the **Build logs** from each of the steps that were run
  - [ ] See links to the generated images in the **Build Artifacts** tab
  - [ ] Note the full name of the generated image `gcr.io/.../...:latest`

- [ ] Deploy the container image to a server on [Compute Engine](https://console.cloud.google.com/compute/instances)

  - [ ] Click **Create Instance** from the **VM instances** page
  - [ ] Use a descriptive **Name**, such as `web-server`
  - [ ] For **Region**, select `us-west1 (Oregon)` and leave the default **Zone**
  - [ ] For **Machine configuration**, choose `E2` for **Series** and `e2-micro` for **Machine type**
  - [ ] Click **Deploy Container** under **Container**
  - [ ] For **Container image**, enter the full name of the generated image
  - [ ] Under **Firewall**, click to **Allow HTTP traffic**
  - [ ] Edit additional settings under **Networking, disks, security, management, sole-tenancy**
    - [ ] Click the default under **Network interfaces** within **Networking**
    - [ ] Select **Create IP Address** under **External IPv4 address**
    - [ ] Enter a name, a reasonable description, and click **Reserve**
    - [ ] Within **Management**, find **Metadata** and **Add item** with **Key** of `google-logging-enabled` and **Value** of `true`
  - [ ] Click **Create** to create the instance

- [ ] Access the server on port 80 of the **External IP** shown in the table

  - [ ] If the server isn't working, troubleshoot using SSH

    ```
    gcloud compute ssh web-server
    docker ps
    ```

### Submission

- [ ] Submit any config changes for review on Gerrit
- [ ] Have the TL fill out the team submission form

 