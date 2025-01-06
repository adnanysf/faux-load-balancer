/**
 * @file main.cpp
 * @brief Main program for load balancer simulation.
 */

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "Loadbalancer.cpp"

/**
 * @brief Generates a random IP address.
 * @return A string representing a random IP address.
 */
std::string generateRandomIP() {
    return std::to_string(rand() % 256) + "." + 
           std::to_string(rand() % 256) + "." + 
           std::to_string(rand() % 256) + "." + 
           std::to_string(rand() % 256);
}

/**
 * @brief Generates a random Request object.
 * @return A Request object with random IP addresses, processing time, and job type.
 */
Request generateRandomRequest() {
    std::string ipIn = generateRandomIP();
    std::string ipOut = generateRandomIP();
    int processingTime = rand() % 10 + 1;
    char jobType = (rand() % 2 == 0) ? 'S' : 'P'; 
    
    return Request(ipIn, ipOut, processingTime, jobType);
}

/**
 * @brief Main function to run the load balancer simulation.
 * @return 0 on successful execution.
 */
int main() {
    int numServers, simulationTime;
    std::string ans, blockedIPMin, blockedIPMax;

    // User input for simulation parameters
    std::cout << "Enter number of servers: ";
    std::cin >> numServers;
    std::cout << "Enter amount of clock cycles: ";
    std::cin >> simulationTime;

    std::cout << "Do you want to block a range of IP addresses? (Y/N) ";
    std::cin >> ans;

    LoadBalancer loadBalancer(numServers);

    // Set up IP blocking if requested
    if (ans == "Y" || ans == "y") {
        std::cout << "Enter start range of IP firewall: ";
        std::cin >> blockedIPMin;
        std::cout << "Enter end range of IP firewall: ";
        std::cin >> blockedIPMax;
        std::cout << std::endl;
        loadBalancer.addBlockedIPRange(blockedIPMin, blockedIPMax);
    }    

    // Main simulation loop
    for(int time = 0; time < simulationTime; ++time) {
        // Generate random requests
        std::vector<Request> randomRequests;
        if(time % 100 < 10) {
            int numRequests = rand() % 10 + 1;
            for(int i = 0; i < numRequests; ++i) {
                Request request = generateRandomRequest();
                randomRequests.push_back(request);
            }
        }

        // Queue generated requests
        for(int i = 0; i < randomRequests.size(); ++i) {
            loadBalancer.queueRequest(randomRequests[i]);
        }
        
        // Process requests
        loadBalancer.processRequests();

        // Update servers periodically
        if(time % 20 == 0 && time != 0) {
            loadBalancer.updateServers(time);
        }
    }

    // Print simulation results
    std::cout << "Simulation complete!" << std::endl;
    loadBalancer.printStats();

    return 0;
}
