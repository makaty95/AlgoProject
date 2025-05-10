#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include "Types.h"
#include <vector>
#include <string>
using namespace std;

double EuclideanDistance(double x1, double y1, double x2, double y2);

void ReadInputs(string file_path, vector<Intersection>& intersections,
    vector<vector<Road>>& graph);

void ReadQueries(string& file_path, vector<Query>& queries);

void printData(vector<Intersection>& intersections,
    vector<vector<Road>>& graph,
    vector<Query>& queries);

void printResult(const std::string& filename , vector<Result>& results, const std::chrono::steady_clock::time_point& timeWithIO);


#endif 

