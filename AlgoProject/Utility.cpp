#include "Utility.h"
#include <fstream>



bool MapData::isDragging = false;
std::vector<std::vector<DS::Edge>> MapData::graph = std::vector<std::vector<DS::Edge>>();
std::vector<DS::Node> MapData::nodes = std::vector<DS::Node>();
DS::Node  MapData::draggingNode = DS::Node();


double Geometry::EuclideanDistance(double x1, double y1, double x2, double y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double Geometry::EuclideanDistance(DS::Point a, DS::Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}



int FIO::ReadInputs(
    std::string                             file_path,
    std::vector<DS::Node>&                  nodes,
    std::vector<std::vector<DS::Edge>>&     graph
) {

    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error opening map file: " << file_path << "\n";
        return -1;
    }

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

