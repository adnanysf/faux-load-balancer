/**
 * @file Request.cpp
 * @brief Defines the Request structure for handling job requests.
 */

#include <iostream>
#include <string> 
#include <vector>
#pragma once

/**
 * @struct Request
 * @brief Represents a job request with input and output IP addresses, time, and job type.
 */
struct Request {
    std::string ipIn;    /**< Input IP address */
    std::string ipOut;   /**< Output IP address */
    int time;            /**< Time of the request */
    char jobType;        /**< Type of the job */

    /**
     * @brief Constructor for creating a Request object.
     * @param in Input IP address
     * @param out Output IP address
     * @param time Time of the request
     * @param type Type of the job
     */
    Request(std::string in, std::string out, int time, char type)
        : ipIn(in), ipOut(out), time(time), jobType(type) {}
};
