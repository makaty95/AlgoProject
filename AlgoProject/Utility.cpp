#include "Utility.h"
#include <fstream>


// Initializing static map data
//bool MapData::isDragging = false;
//DS::Node  MapData::draggingNode = DS::Node();
std::vector<std::vector<DS::Edge>> MapData::graph = std::vector<std::vector<DS::Edge>>();
std::vector<DS::Node> MapData::nodes = std::vector<DS::Node>();
bool MapData::isLoaded = false;
int MapData::N = 0;
int MapData::M = 0;
int MapData::defaultRadius = 1;
Visuals::DrawUtil MapData::drawUtil = Visuals::DrawUtil();
double MapData::zoomFactor = 1.0;
DS::Point MapData::zoomCenter = DS::Point();
////////////////////////////////////////////////////////////////////////

double Geometry::EuclideanDistance(double x1, double y1, double x2, double y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double Geometry::EuclideanDistance(DS::Point a, DS::Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void FIO::ResetAll() {
    MapData::nodes.clear();
    MapData::graph.clear();
    MapData::isLoaded = false;
    MapData::N = 0;
    MapData::M = 0;
}

int FIO::ReadMap(
    std::string                             file_path,
    std::vector<DS::Node>&                  nodes,
    std::vector<std::vector<DS::Edge>>&     graph
) {
    
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error opening map file: " << file_path << "\n";
        return -1;
    }

    FIO::ResetAll();

    int N;
    file >> N;
    nodes.resize(N);
    graph.resize(N);
    for (int i = 0; i < N; ++i) {
        int id;
        double x, y;
        file >> id >> x >> y;
        nodes[id] = DS::Node(x, y);
    }



    int M;
    file >> M;
    for (int i = 0; i < M; ++i) {
        int u, v;
        double length, speed;
        file >> u >> v >> length >> speed;
        double time = (length / speed) * 60.0;
        graph[u].push_back(DS::Edge( v, length, speed, time));
        graph[v].push_back(DS::Edge(u, length, speed, time));
    }

    file.close();



    // utility for map visualizing
    MapData::N = N;
    MapData::M = M;
    MapData::drawUtil.max_x = MapData::drawUtil.min_x = nodes[0].loc.x;
    MapData::drawUtil.max_y = MapData::drawUtil.min_y = nodes[0].loc.y;
    for (int i = 0; i < N; i++) {
        double x = nodes[i].loc.x;
        double y = nodes[i].loc.y;
        nodes[i].properties.radius = MapData::defaultRadius;
        nodes[i].properties.isSelected = false;
        MapData::drawUtil.max_x = std::max(MapData::drawUtil.max_x, x);
        MapData::drawUtil.max_y = std::max(MapData::drawUtil.max_y, y);
        MapData::drawUtil.min_x = std::min(MapData::drawUtil.min_x, x);
        MapData::drawUtil.min_y = std::min(MapData::drawUtil.min_y, y);
    }

    MapData::isLoaded = true;
    return 0;


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

    double min_x = MapData::drawUtil.min_x;
    double min_y = MapData::drawUtil.min_y;
    double max_x = MapData::drawUtil.max_x;
    double max_y = MapData::drawUtil.max_y;
    double w = MapData::drawUtil.W, h = MapData::drawUtil.H;


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