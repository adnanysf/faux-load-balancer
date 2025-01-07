# Faux Load Balancer

## Overview

This project implements a load balancer that manages load distribution between servers, processes requests, and handles blocked IPs. The load balancer dynamically adjusts the number of servers based on the current load and provides statistics about its performance.

## Project Structure

```
html/
    _loadbalancer_8cpp_source.html
    _requests_8cpp_source.html
    _webserver_8cpp_source.html
    annotated_dup.js
    annotated.html
    class_load_balancer-members.html
    class_load_balancer.html
    class_load_balancer.js
    class_web_server-members.html
    class_web_server.html
    class_web_server.js
    classes.html
    clipboard.js
    cookie.js
    doxygen_crawl.html
    doxygen.css
    dynsections.js
    ...
latex/
    ...
Loadbalancer.cpp
main.cpp
Requests.cpp
Webserver.cpp
```

## Key Classes and Functions

### LoadBalancer

- **Class Description**: Manages load balancing between servers, processes requests, and handles blocked IPs.
- **File**: 

Loadbalancer.cpp



#### Key Methods

- **`LoadBalancer::LoadBalancer(int numServers)`**
  - Constructs a LoadBalancer with a specified number of servers.

- **`void LoadBalancer::increaseServers(int numAdded, int clockCycle)`**
  - Increases the number of servers by a specified amount.
  - Implementation

- **`void LoadBalancer::decreaseServers(int clockCycle)`**
  - Decreases the number of idle servers.
  - Implementation

- **`void LoadBalancer::updateServers(int clockCycle)`**
  - Updates the number of servers based on current load.
  - Implementation

- **`void LoadBalancer::processRequests()`**
  - Processes requests by assigning them to available servers.
  - Implementation

- **`void LoadBalancer::printStats() const`**
  - Prints statistics about the load balancer's performance.
  - Implementation

### WebServer

- **Class Description**: Represents a web server that can process requests.
- **File**: 

Webserver.cpp



### Request

- **Class Description**: Represents a request to be processed by the load balancer.
- **File**: 

Requests.cpp



## Building and Running

To build the project, use the following command:

```sh
g++ -o loadbalancer main.cpp Loadbalancer.cpp Requests.cpp Webserver.cpp
```

To run the project, use the following command:

```sh
./loadbalancer
```

## Documentation

The project documentation is generated using Doxygen and can be found in the 

html

 and 

latex

 directories. Open 

index.html

 in a web browser to view the documentation.

## License

This project is licensed under the MIT License. See the LICENSE file for details.

adnanysf: put in readme format

Workspace: # Load Balancer Project

## Overview

This project implements a load balancer that manages load distribution between servers, processes requests, and handles blocked IPs. The load balancer dynamically adjusts the number of servers based on the current load and provides statistics about its performance.

## Project Structure

```
.DS_Store
.vscode/
    settings.json
a.out
html/
    _loadbalancer_8cpp_source.html
    _requests_8cpp_source.html
    _webserver_8cpp_source.html
    annotated_dup.js
    annotated.html
    class_load_balancer-members.html
    class_load_balancer.html
    class_load_balancer.js
    class_web_server-members.html
    class_web_server.html
    class_web_server.js
    classes.html
    clipboard.js
    cookie.js
    doxygen_crawl.html
    doxygen.css
    dynsections.js
    ...
latex/
    ...
Loadbalancer.cpp
main.cpp
Requests.cpp
Webserver.cpp
```

## Key Classes and Functions

### LoadBalancer

- **Class Description**: Manages load balancing between servers, processes requests, and handles blocked IPs.
- **File**: 

Loadbalancer.cpp



#### Key Methods

- **`LoadBalancer::LoadBalancer(int numServers)`**
  - Constructs a LoadBalancer with a specified number of servers.

- **`void LoadBalancer::increaseServers(int numAdded, int clockCycle)`**
  - Increases the number of servers by a specified amount.

- **`void LoadBalancer::decreaseServers(int clockCycle)`**
  - Decreases the number of idle servers.

- **`void LoadBalancer::updateServers(int clockCycle)`**
  - Updates the number of servers based on current load.
  - Implementation:
    ```cpp
    void updateServers(int clockCycle){
        int numServersNeeded = (streamingQueue.size() + processingQueue.size())/30;
        int numServers = numServersNeeded - servers.size();

        if (numServers > 0) {
            increaseServers(numServers, clockCycle);
        } else if (numServers < 0) {
            decreaseServers(clockCycle);
        }
    }
    ```

- **`void LoadBalancer::processRequests()`**
  - Processes requests by assigning them to available servers.

- **`void LoadBalancer::printStats() const`**
  - Prints statistics about the load balancer's performance.

- **`uint32_t LoadBalancer::ipToInteger(const std::string &ip)`**
  - Converts an IPv4 address from string format to a 32-bit integer.
  - Documentation: class_load_balancer.html

### WebServer

- **Class Description**: Represents a web server that can process requests.
- **File**: 

Webserver.cpp



### Request

- **Class Description**: Represents a request to be processed by the load balancer.
- **File**: 

Requests.cpp



## Building and Running

To build the project, use the following command:

```sh
g++ -o loadbalancer main.cpp Loadbalancer.cpp Requests.cpp Webserver.cpp
```

To run the project, use the following command:

```sh
./loadbalancer
```

## Documentation

The project documentation is generated using Doxygen and can be found in the 

html

 and 

latex

 directories. Open 

index.html

 in a web browser to view the documentation.
