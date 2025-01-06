#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "Loadbalancer.cpp"

std::string generateRandomIP() {
    return std::to_string(rand() % 256) + "." + 
           std::to_string(rand() % 256) + "." + 
           std::to_string(rand() % 256) + "." + 
           std::to_string(rand() % 256);
}

Request generateRandomRequest() {
    std::string ipIn = generateRandomIP();
    std::string ipOut = generateRandomIP();
    int processingTime = rand() % 10 + 1;
    char jobType = (rand() % 2 == 0) ? 'S' : 'P'; 
    
    return Request(ipIn, ipOut, processingTime, jobType);
}


int main(){
    int numServers, simulationTime;
    std::cout << "Enter number of servers: ";
    std::cin >> numServers;
    std::cout << "Enter amount of clock cycles: ";
    std::cin >> simulationTime;

    LoadBalancer loadBalancer(numServers);

    for(int time = 0; time < simulationTime; ++time) {

        std::vector<Request> randomRequests;
        if(time % 100 < 10){
            int numRequests = rand() % 10 + 1;
            for(int i = 0; i < numRequests; ++i){
                Request request = generateRandomRequest();
                randomRequests.push_back(request);
            }
        }

        for(int i = 0; i < randomRequests.size(); ++i){
            loadBalancer.queueRequest(randomRequests[i]);
        }
        
        loadBalancer.processRequests();

        if(time % 20 == 0){
            loadBalancer.updateServers(time);
        }

    }

    std::cout << "Simulation complete!" << std::endl;
    loadBalancer.printStats();

    
    return 0;
}