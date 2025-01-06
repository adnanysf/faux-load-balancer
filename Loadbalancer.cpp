#include <iostream>
#include <string> 
#include <vector>
#include <queue>
#include <arpa/inet.h>
#include "Requests.cpp"
#include "WebServer.cpp"

class LoadBalancer {
private:
    std::vector<WebServer> servers;
    std::queue<Request> streamingQueue;
    std::queue<Request> processingQueue;
    std::pair<uint32_t, uint32_t> blockedRange = {};
    int numberOfRequests = 0;
    int numberOfServersAdded = 0;
    int numberOfServersRemoved = 0;
    int numberOfBlockedRequests = 0;

    int currentTime;

public:
    LoadBalancer(int numServers){
        for (int i = 0; i < numServers; ++i) {
            servers.push_back(WebServer("0",0));
        }
        currentTime = 0;
    }

    uint32_t ipToInteger(const std::string& ip) {
        struct sockaddr_in sa;
        inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr));
        return ntohl(sa.sin_addr.s_addr);
    }

    bool isBlocked(uint32_t ip) {
        if (ip >= blockedRange.first && ip <= blockedRange.second) {
            return true;
        }
        return false;
    }

    void addBlockedIPRange(std::string start, std::string end){
        blockedRange = {ipToInteger(start), ipToInteger(end)};
    }

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

    bool isFull() const {
        return streamingQueue.size() + processingQueue.size() > servers.size() * 30;
    }

    void increaseServers(int numAdded, int clockCycle){
        for (int i = 0; i < numAdded; i++) {
            servers.push_back(WebServer("0",0));
        }
        numberOfServersAdded += numAdded;
        std::cout << clockCycle << ": Added " << numAdded << " servers." << std::endl;
    }

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

    void updateServers(int clockCycle){
        int numServersNeeded = (streamingQueue.size() + processingQueue.size())/30;
        int numServers = numServersNeeded - servers.size();

        if (numServers > 0) {
            increaseServers(numServers, clockCycle);
        } else if (numServers < 0) {
            decreaseServers(clockCycle);
        }
    }

    void printStats() const {
        std::cout << "Number of requests: " << numberOfRequests << std::endl;
        std::cout << "Number of blocked requests: " << numberOfBlockedRequests << std::endl;
        std::cout << "Number of servers added: " << numberOfServersAdded << std::endl;
        std::cout << "Number of servers removed: " << numberOfServersRemoved << std::endl;
    }

    bool areQueuesEmpty() const {
        return streamingQueue.empty() && processingQueue.empty();
    }
};
