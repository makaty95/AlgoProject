#pragma once
#include <iostream>
#include "FileHandling.h"
#include <vector>

//class PathFinder {
//public:
//    static std::vector<DS::Node> intersections;
//    static std::vector<std::vector<DS::Edge>> graph;
//    static std::vector<DS::Query> queries;
//    static std::vector<Result> results;
//
//    
//};

// Somewhere at the top of your source file or in a header

class PathFinder {
public:
    static void InitializeKDTree();
};

void Start();

inline std::vector<DS::Edge> FindAdjacentNodes(const DS::Node& point, double R);
inline void Dijkstra(int start, int end);
inline void get_res(const std::vector<std::pair<int, int>>& parent, int start, int end, const std::vector<double>& times);

