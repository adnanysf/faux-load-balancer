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
    std::string ans, blockedIPMin, blockedIPMax;

    std::cout << "Enter number of servers: ";
    std::cin >> numServers;
    std::cout << "Enter amount of clock cycles: ";
    std::cin >> simulationTime;

    std::cout << "Do you want to block a range of IP addresses? (Y/N) ";
    std::cin >> ans;

    LoadBalancer loadBalancer(numServers);

    if (ans == "Y" || ans == "y"){
        std::cout << "Enter start range of IP firewall: ";
        std::cin >> blockedIPMin;
        std::cout << "Enter end range of IP firewall: ";
        std::cin >> blockedIPMax;
        std::cout << std::endl;
        loadBalancer.addBlockedIPRange(blockedIPMin, blockedIPMax);
    }    

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

        if(time % 20 == 0 && time != 0){
            loadBalancer.updateServers(time);
        }

    }

    std::cout << "Simulation complete!" << std::endl;
    loadBalancer.printStats();

    
    return 0;
}