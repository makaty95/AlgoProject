#pragma once

#ifndef TYPES_H
#define TYPES_H
#include <vector>

class Intersection {
public:
    double x, y;
};

class Road {
public:
    int neighbor_id;
    double length;
    double speed;
    double time;
};

class Query {
public:
    double x_s, y_s, x_d, y_d, R;
};

#include <chrono> // for steady_clock and time_point

class Result {
public:
    std::vector<int> pathId;
    double totalDistance = 0.0;
    double shortestTime = 0.0;
    double walkingDistance = 0.0;
    double vehicleDistance = 0.0;

    


    // Member to store elapsed time (without I/O)
    static double elapsedTimeWithoutIO;
    static double elapsedTimeWithIO ;
};






#endif 
