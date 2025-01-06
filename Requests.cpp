#include <iostream>
#include <string> 
#include <vector>
#pragma once

struct Request {
    std::string ipIn;
    std::string ipOut;
    int time;
    char jobType;

    Request(std::string in, std::string out, int time, char type)
        : ipIn(in), ipOut(out), time(time), jobType(type) {}
};
