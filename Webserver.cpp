#include "Requests.cpp"
#include <iostream>

class WebServer {
private:
    int id;
    bool isBusy;
    Request* currentRequest;

public:
    WebServer(int serverId) : id(serverId), isBusy(false), currentRequest(nullptr) {}

    bool processRequest(Request* request);
    bool isAvailable() const {
        return !isBusy;
        }
};