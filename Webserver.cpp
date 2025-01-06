#include "Requests.cpp"
#include <iostream>
#include <queue>
#include <vector>
#include <string>

class WebServer {
private:
    std::string id;
    bool isBusy;
    Request* currentRequest;
    int timeLeft;
    

public:
    WebServer(std::string serverId, int timeLeft) : id(serverId), isBusy(false), currentRequest(nullptr), timeLeft(timeLeft) {}

    void processRequest(){
        if(!isBusy) {
            return;
        }
        timeLeft--;
        if (timeLeft == 0) {
            isBusy = false;
            currentRequest = nullptr;
            id = "0";
        }
    }

    bool isAvailable() const {
        return !isBusy;
    }

    void addRequest(Request* request) {
        currentRequest = request;
        id = request->ipIn;
        isBusy = true;
        timeLeft = request->time;
    }

    int getTimeLeft() {
        return timeLeft;
    }
    
    std::string getId() {
        return id;
    }
};