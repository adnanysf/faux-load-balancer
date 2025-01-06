#include <iostream>
#include <string> 
#include <vector>
#include <queue>
#include <arpa/inet.h>
#include "Requests.cpp"
#include "WebServer.cpp"

/**
 * @class LoadBalancer
 * @brief Manages load balancing between servers, processes requests, and handles blocked IPs.
 */
class LoadBalancer {
private:
    std::vector<WebServer> servers; ///< List of servers managed by the load balancer.
    std::queue<Request> streamingQueue; ///< Queue for streaming requests.
    std::queue<Request> processingQueue; ///< Queue for processing requests.
    std::pair<uint32_t, uint32_t> blockedRange; ///< Range of blocked IPs.
    int numberOfRequests = 0; ///< Total number of requests received.
    int numberOfServersAdded = 0; ///< Total number of servers added.
    int numberOfServersRemoved = 0; ///< Total number of servers removed.
    int numberOfBlockedRequests = 0; ///< Total number of blocked requests.

    int currentTime; ///< Current time in the system.

public:
    /**
     * @brief Constructs a LoadBalancer with a specified number of servers.
     * @param numServers The initial number of servers.
     */
    LoadBalancer(int numServers){
        for (int i = 0; i < numServers; ++i) {
            servers.push_back(WebServer("0",0));
        }
        currentTime = 0;
    }

    /**
     * @brief Converts an IPv4 address from string format to a 32-bit integer.
     * @param ip The IPv4 address in string format (e.g., "192.168.1.1").
     * @return The IPv4 address as a 32-bit integer in host byte order.
     */
    uint32_t ipToInteger(const std::string& ip) {
        struct sockaddr_in sa;
        inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr));
        return ntohl(sa.sin_addr.s_addr);
    }

    /**
     * @brief Checks if an IP address is within the blocked range.
     * @param ip The IPv4 address as a 32-bit integer.
     * @return True if the IP is blocked, false otherwise.
     */
    bool isBlocked(uint32_t ip) {
        if (ip >= blockedRange.first && ip <= blockedRange.second) {
            return true;
        }
        return false;
    }

    /**
     * @brief Adds a range of IPs to the blocked list.
     * @param start The start of the blocked IP range in string format.
     * @param end The end of the blocked IP range in string format.
     */
    void addBlockedIPRange(std::string start, std::string end){
        blockedRange.first = ipToInteger(start);
        blockedRange.second = ipToInteger(end);
    }

    /**
     * @brief Adds a request to the appropriate queue.
     * @param request The request to be queued.
     */
    void queueRequest(const Request& request){
        numberOfRequests++;
        if (isBlocked(ipToInteger(request.ipIn))){
            numberOfBlockedRequests++;
            std::cout << "Blocked request from " << request.ipIn << std::endl;
            return;
        }

        if (request.jobType == 'S') {
            streamingQueue.push(request);
        } else {
            processingQueue.push(request);
        }
    }

    /**
     * @brief Processes requests by assigning them to available servers.
     */
    void processRequests(){
        for (int i = 0; i < servers.size(); ++i) {
            if (!servers[i].isAvailable()) {
                servers[i].processRequest();
            }
            else{
                if (!streamingQueue.empty()) {
                    Request request = streamingQueue.front();
                    streamingQueue.pop();
                    servers[i].addRequest(&request);
                }
                else if (!processingQueue.empty()) {
                    Request request = processingQueue.front();
                    processingQueue.pop();
                    servers[i].addRequest(&request);
                }
            }
        }
    }

    /**
     * @brief Checks if the load balancer is overloaded.
     * @return True if the combined queue size exceeds the servers' capacity, false otherwise.
     */
    bool isFull() const {
        return streamingQueue.size() + processingQueue.size() > servers.size() * 30;
    }

    /**
     * @brief Increases the number of servers by a specified amount.
     * @param numAdded The number of servers to add.
     * @param clockCycle The current clock cycle when the servers are added.
     */
    void increaseServers(int numAdded, int clockCycle){
        for (int i = 0; i < numAdded; i++) {
            servers.push_back(WebServer("0",0));
        }
        numberOfServersAdded += numAdded;
        std::cout << clockCycle << ": Added " << numAdded << " servers." << std::endl;
    }

    /**
     * @brief Decreases the number of idle servers.
     * @param clockCycle The current clock cycle when the servers are removed.
     */
    void decreaseServers(int clockCycle){
        int numRemoved = 0;
        for (int i = 0; i < servers.size(); ++i) {
            if(servers[i].getId() == "0"){
                servers.erase(servers.begin() + i);
                numRemoved++;
            }
        }
        if (numRemoved > 0) {
            numberOfServersRemoved += numRemoved;
            std::cout << clockCycle << ": Removed " << numRemoved << " servers." << std::endl;
        }
    }

    /**
     * @brief Updates the number of servers based on current load.
     * @param clockCycle The current clock cycle during the update.
     */
    void updateServers(int clockCycle){
        int numServersNeeded = (streamingQueue.size() + processingQueue.size())/30;
        int numServers = numServersNeeded - servers.size();

        if (numServers > 0) {
            increaseServers(numServers, clockCycle);
        } else if (numServers < 0) {
            decreaseServers(clockCycle);
        }
    }

    /**
     * @brief Prints statistics about the load balancer's performance.
     */
    void printStats() const {
        std::cout << "Number of requests: " << numberOfRequests << std::endl;
        std::cout << "Number of blocked requests: " << numberOfBlockedRequests << std::endl;
        std::cout << "Number of servers added: " << numberOfServersAdded << std::endl;
        std::cout << "Number of servers removed: " << numberOfServersRemoved << std::endl;
    }

    /**
     * @brief Checks if both the streaming and processing queues are empty.
     * @return True if both queues are empty, false otherwise.
     */
    bool areQueuesEmpty() const {
        return streamingQueue.empty() && processingQueue.empty();
    }
};
