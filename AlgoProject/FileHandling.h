#pragma once

#include "Types.h"
#include <vector>
#include <string>
using namespace std;

void ResetAll();

namespace FIO {
    int ReadMap(
        std::string                             file_path,
        std::vector<DS::Node>&                  intersections,
        std::vector<std::vector<DS::Edge>>&     graph
    );

    int ReadQueries(string& file_path, vector<DS::Query>& queries);

    void printResult(const std::string& filename, vector<Result>& results, const std::chrono::steady_clock::time_point& timeWithIO);

}


//double EuclideanDistance(double x1, double y1, double x2, double y2);

//void ReadInputs(string file_path, vector<Intersection>& intersections,
//    vector<vector<Road>>& graph);



//void printData(vector<Intersection>& intersections,
//    vector<vector<Road>>& graph,
//    vector<Query>& queries);
