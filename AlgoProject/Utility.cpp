#include "Utility.h"
#include "Types.h"
#include <fstream>


// Initializing static map data
//bool MapData::isDragging = false;
//DS::Node  MapData::draggingNode = DS::Node();


////////////////////////////////////////////////////////////////////////




double Geometry::EuclideanDistance(double x1, double y1, double x2, double y2) {
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double Geometry::EuclideanDistance(DS::Point a, DS::Point b) {
    return EuclideanDistance(a.x, a.y, b.x, b.y);
}


void Debug::PrintMapData(
    std::vector<DS::Node>& nodes,
    std::vector<std::vector<DS::Edge>>& graph
) {

    std::cout << "Nodes:\n";
    for (int i = 0; i < nodes.size(); ++i) {
        std::cout << "ID " << i << ": (" << nodes[i].loc.x << ", "
            << nodes[i].loc.y << ")\n";
    }

    std::cout << "\nGraph (Adjacency List):\n";
    for (int u = 0; u < graph.size(); u++) {
        std::cout << "Node " << u << ": ";
        for (const auto& edge : graph[u]) {
            std::cout << "(Neighbor: " << edge.neighbor_id
                << ", Length: " << edge.length
                << ", Speed: " << edge.speed
                << ", Time: " << edge.time << ") ";
        }
        std::cout << "\n";
    }

}



void Debug::PrintQueriesData(std::vector<DS::Query>& queries) {

    std::cout << "\nQueries:\n";
    for (int i = 0; i < queries.size(); ++i) {
        auto q = queries[i];
        std::cout << "Query " << i + 1 << ": Source=(" << q.S.x << ", " << q.S.y
            << "), Destination=(" << q.E.x << ", " << q.E.y
            << "), R=" << q.R << " km\n";
    }

}



DS::Point Visuals::normalize(double x, double y) {

    double min_x = MapData::drawInfo.min_x;
    double min_y = MapData::drawInfo.min_y;
    double max_x = MapData::drawInfo.max_x;
    double max_y = MapData::drawInfo.max_y;
    double w = MapData::drawInfo.W, h = MapData::drawInfo.H;


    // new normalized coordinates
    double _x = w * ((x - min_x) / (max_x - min_x));
    double _y = h - ((y - min_y) / (max_y - min_y)) * h;

    // apply some padding
    double e = 20;
    if (_x < e) _x += e;
    if (_y < e) _y += e;
    if (_x > (w - e)) _x -= e;
    if(_y > (h - e)) _y -= e;

    /*printf("factor: %f\n", Visuals::zoomFactor);
    printf("before: %f, %f\n", _x, _y);
    printf("after: %f, %f\n", _x * zoomFactor, _y * zoomFactor);*/

    DS::Point ret = zoom(DS::Point(_x, _y));
    //printf("before: %f, %f \n after: %f, %f \n", _x, _y, ret.x, ret.y);
    
    // handle mouse dragging 
    ret.x += MapData::panOffset.x;
    ret.y += MapData::panOffset.y;

    return ret;
}

DS::Point Visuals::normalize(DS::Point p) {
    return normalize(p.x, p.y);
}

// apply some scale to the points to make a zoom
std::vector<DS::Point> Visuals::zoom() {
    std::vector<DS::Point> ret(MapData::N);
    int idx = 0;
    for (DS::Node node : MapData::nodes) {
        
        // translate to origin
        ret[idx].x = node.loc.x - MapData::zoomCenter.x;
        ret[idx].y = node.loc.y - MapData::zoomCenter.y;
    
        // scaling
        ret[idx].x *= MapData::zoomFactor;
        ret[idx].y *= MapData::zoomFactor;

        // translation back
        ret[idx].x += MapData::zoomCenter.x;
        ret[idx].y += MapData::zoomCenter.y;
    }

    return ret;
}


DS::Point Visuals::zoom(DS::Point p) {
    DS::Point ret = p;
 
    // translate to origin
    ret.x -= MapData::zoomCenter.x;
    ret.y -= MapData::zoomCenter.y;

    // scaling
    ret.x *= MapData::zoomFactor;
    ret.y *= MapData::zoomFactor;

    // translation back
    ret.x += MapData::zoomCenter.x;
    ret.y += MapData::zoomCenter.y;
    

    return ret;
}