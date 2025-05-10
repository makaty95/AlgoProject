#pragma once

#include "Types.h"
#include "FileHandling.h"
#include <vector>
#include <utility>

class PathFinder {
public:
    static std::vector<Intersection> intersections;
    static std::vector<std::vector<Road>> graph;
    static std::vector<Query> queries;
    static std::vector<Result> results;

    
};

 void Start();
 std::vector<Road> FindAdjacentNodes(const Intersection& point, double R);
 void Dijkstra(int start, int end);
 void get_res(const std::vector<std::pair<int, int>>& parent, int start, int end, const std::vector<double>& times);

