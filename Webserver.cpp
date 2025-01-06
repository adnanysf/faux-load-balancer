#include "Requests.cpp"
#include <iostream>
#include <queue>
#include <vector>
#include <string>

/**
 * @class WebServer
 * @brief Represents a single web server that processes requests.
 */
class WebServer {
private:
    std::string id; ///< The ID of the server or the ID of the request being processed.
    bool isBusy; ///< Indicates whether the server is currently processing a request.
    Request* currentRequest; ///< Pointer to the current request being processed.
    int timeLeft; ///< Time left to complete the current request.

public:
    /**
     * @brief Constructs a WebServer with a specific ID and initial time left.
     * @param serverId The ID of the server.
     * @param timeLeft The initial time left to process a request.
     */
    WebServer(std::string serverId, int timeLeft) : id(serverId), isBusy(false), currentRequest(nullptr), timeLeft(timeLeft) {}

    /**
     * @brief Processes the current request, reducing its remaining time.
     * If the request is complete, the server becomes available.
     */
    void processRequest() {
        if (!isBusy) {
            return;
        }
        timeLeft--;
        if (timeLeft == 0) {
            isBusy = false;
            currentRequest = nullptr;
            id = "0";
        }
    }

    /**
     * @brief Checks if the server is available for a new request.
     * @return True if the server is available, false otherwise.
     */
    bool isAvailable() const {
        return !isBusy;
    }

    /**
     * @brief Assigns a new request to the server.
     * @param request Pointer to the request to be processed.
     */
    void addRequest(Request* request) {
        currentRequest = request;
        id = request->ipIn;
        isBusy = true;
        timeLeft = request->time;
    }

    /**
     * @brief Gets the time left for the current request to complete.
     * @return The time left to complete the current request.
     */
    int getTimeLeft() {
        return timeLeft;
    }

    /**
     * @brief Gets the ID of the server or the current request.
     * @return The server's ID or the ID of the current request being processed.
     */
    std::string getId() {
        return id;
    }
};