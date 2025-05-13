#pragma once
#include <vector>
#include <chrono> // for steady_clock and time_point

namespace DS {
    class Prop {
    public:
        int radius;
        bool isSelected;
    };

    class Point {
    public:
        double x, y;
        Point(double x, double y) : x(x), y(y) {}
        Point() {}
    };

    class Node {
    public:
        DS::Prop properties;
        DS::Point loc;
        Node(double x, double y) : loc(DS::Point(x, y)) {}
        Node(DS::Point pnt) : loc(pnt) {}
        Node() {}
    };

    class Edge {
    public:
        Edge() {}
        Edge(int neighbor_id, double length, double speed, double time) :
            neighbor_id(neighbor_id), length(length), time(time), speed(speed) {
        }

        int neighbor_id;
        double length;
        double speed;
        double time;
    };

    class Query {
    public:
        Query(DS::Point start, DS::Point end, double r) : S(start), E(end), R(r) {}
        DS::Point S, E;
        double R;
    };

    class DrawInfo {
    public:
        DrawInfo(double W = 0, double H = 0) {
            this->H = H;
            this->W = W;
        }
        double min_x, min_y, max_x, max_y;
        double W, H; // width and height of the panel to draw on

    };
}


//class Intersection {
//public:
//    double x, y;
//};

//class Road {
//public:
//    int neighbor_id;
//    double length;
//    double speed;
//    double time;
//};

//class Query {
//public:
//    double x_s, y_s, x_d, y_d, R;
//};



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


class MapData {
public:
    static double zoomFactor;
    static DS::Point zoomCenter;
    static DS::DrawInfo drawInfo;
    static int defaultRadius;
    static bool isLoaded;
    static int N, M;

    static std::vector<std::vector<DS::Edge>> graph;
    static std::vector<DS::Node> nodes;
    static std::vector<DS::Query> queries;
    static std::vector<Result> results;

    //static DS::Node draggingNode;
    //static bool isDragging;
};