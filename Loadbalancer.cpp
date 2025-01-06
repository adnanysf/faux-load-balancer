#include <iostream>
#include <string> 
#include <vector>
#include <queue>
#include "Requests.cpp"
#include "WebServer.cpp"

class LoadBalancer {
private:
    std::vector<WebServer> servers;
    std::queue<Request> streamingQueue;
    std::queue<Request> processingQueue; 
    int numberOfRequests = 0;
    int numberOfServersAdded = 0;
    int numberOfServersRemoved = 0;
    int currentTime;

public:
    LoadBalancer(int numServers){
        for (int i = 0; i < numServers; ++i) {
            servers.push_back(WebServer("0",0));
        }
        currentTime = 0;
    }

    void queueRequest(const Request& request){
        if (request.jobType == 'S') {
            streamingQueue.push(request);
        } else {
            processingQueue.push(request);
        }
        numberOfRequests++;
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
        std::cout << "Added " << numAdded << " servers at " << clockCycle << " Clock Cycles" << std::endl;
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
            std::cout << "Removed " << numRemoved << " servers at " << clockCycle << " Clock Cycles" << std::endl;
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
        std::cout << "Number of servers added: " << numberOfServersAdded << std::endl;
        std::cout << "Number of servers removed: " << numberOfServersRemoved << std::endl;
    }

    bool areQueuesEmpty() const {
        return streamingQueue.empty() && processingQueue.empty();
    }
};
