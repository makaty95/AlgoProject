#pragma once
#include <vector>
#include <string>
#include <iostream>


namespace DS {
    class Prop {
    public:
        int radius;
        bool isSelected;
    };

    class Point {
    public:
        double x, y;
        Point(double x, double y) : x(x), y(y){}
        Point(){}
    };

    class Node {
    public:
        DS::Prop properties;
        DS::Point loc;
        Node(double x, double y) : loc(DS::Point(x, y)){}
        Node(DS::Point pnt) : loc(pnt) {}
        Node() { }
    };

    class Edge {
    public:
        Edge(){}
        Edge(int neighbor_id, double length, double speed, double time) : 
            neighbor_id(neighbor_id), length(length), time(time), speed(speed){}
        
        int neighbor_id;
        double length;
        double speed;
        double time;
    };

    class Query {
    public:
        DS::Point S, E;
        double R;
    };
}

namespace Geometry {
    double EuclideanDistance(double x1, double y1, double x2, double y2);
    double EuclideanDistance(DS::Point a, DS::Point b);
}

namespace FIO {
	int ReadMap(
                    std::string                             file_path,
                    std::vector<DS::Node>&                  intersections,
                    std::vector<std::vector<DS::Edge>>&     graph
    );

    void ResetAll();
}

namespace Debug {
    void PrintMapData(
                    std::vector<DS::Node>&              nodes,
                    std::vector<std::vector<DS::Edge>>& graph
    );

    void PrintQueriesData(std::vector<DS::Query>& queries);

}

namespace Visuals {
    void setMapDrawing(bool toSet);
    static double display_scale = 1;
    class DrawUtil {
    public:
        DrawUtil(double W = 0, double H = 0) {
            this->H = H;
            this->W = W;
        }
        double min_x, min_y, max_x, max_y;
        double W, H; // width and height of the panel to draw on

    };
    DS::Point normalize(DS::Point p);
    DS::Point normalize(double x, double y);
}

class MapData {
    public:

        static Visuals::DrawUtil drawUtil;
        static int defaultRadius;
        static bool isLoaded;
        static int N, M;
        static std::vector<std::vector<DS::Edge>> graph;
        static std::vector<DS::Node> nodes;
        //static DS::Node draggingNode;
        //static bool isDragging;
};