#include "FileHandling.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <iomanip> 
using namespace std;



double EuclideanDistance(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void ReadInputs(string file_path, vector<Intersection>& intersections,
    vector<vector<Road>>& graph) {
    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Error opening map file: " << file_path << "\n";
        return;
    }

    int N;
    file >> N;
    intersections.resize(N);
    graph.resize(N);
    for (int i = 0; i < N; ++i) {
        int id;
        double x, y;
        file >> id >> x >> y;
        intersections[id] = { x, y };
    }

    int M;
    file >> M;
    for (int i = 0; i < M; ++i) {
        int u, v;
        double length, speed;
        file >> u >> v >> length >> speed;
        double time = (length / speed) * 60.0;
        graph[u].push_back({ v, length, speed, time });
        graph[v].push_back({ u, length, speed, time });
    }

    file.close();
}

void ReadQueries(string& file_path, vector<Query>& queries) {
    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Error opening queries file: " << file_path << "\n";
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        istringstream iss(line);
        /*int query_id;*/
        double x_s, y_s, x_d, y_d, R;
        if (iss >> x_s >> y_s >> x_d >> y_d >> R) {
            R /= 1000.0;
            queries.push_back({ x_s, y_s, x_d, y_d, R });
        }
    }

    file.close();
}

void printData(vector<Intersection>& intersections,
    vector<vector<Road>>& graph,
    vector<Query>& queries) {
    cout << "Intersections:\n";
    for (int i = 0; i < intersections.size(); ++i) {
        cout << "ID " << i << ": (" << intersections[i].x << ", "
            << intersections[i].y << ")\n";
    }

    cout << "\nGraph (Adjacency List):\n";
    for (int u = 0; u < graph.size(); u++) {
        cout << "Intersection " << u << ": ";
        for (const auto& road : graph[u]) {
            std::cout << "(Neighbor: " << road.neighbor_id
                << ", Length: " << road.length
                << ", Speed: " << road.speed
                << ", Time: " << road.time << ") ";
        }
        cout << "\n";
    }

    cout << "\nQueries:\n";
    for (int i = 0; i < queries.size(); ++i) {
        auto q = queries[i];
        cout << "Query " << i + 1 << ": Source=(" << q.x_s << ", " << q.y_s
            << "), Destination=(" << q.x_d << ", " << q.y_d
            << "), R=" << q.R << " km\n";
    }
}


// Define the static member variables outside of the class
double Result::elapsedTimeWithIO = 0.0;
double Result::elapsedTimeWithoutIO = 0.0;


void printResult(const std::string& filename, vector<Result>& results, const std::chrono::steady_clock::time_point& timeWithIO) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file: " << filename << "\n";
        return;
    }

    for (const auto& res : results)
    {
        // Write path IDs (space-separated)
        for (auto it = res.pathId.rbegin(); it != res.pathId.rend(); ++it) {
            outfile << *it << " ";
        }
        outfile << "\n";

        // Write metrics with 2 decimal precision
        outfile << std::fixed << std::setprecision(2);
        outfile << res.shortestTime << " mins\n";
        outfile << res.totalDistance << " km\n";
        outfile << res.walkingDistance << " km\n";
        outfile << res.vehicleDistance << " km\n\n";
    }

    outfile << Result::elapsedTimeWithoutIO*1000 << " ms\n\n";
    auto endTimeWithIO = std::chrono::steady_clock::now();

    Result::elapsedTimeWithIO = std::chrono::duration_cast<std::chrono::duration<double>>(endTimeWithIO - timeWithIO).count();  // OK

    outfile << Result::elapsedTimeWithIO * 1000 << " ms\n";


    outfile.close();
}
