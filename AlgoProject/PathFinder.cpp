#include "PathFinder.h"
#include <queue>
#include <cfloat>
#include <algorithm>
#include <iostream>

// Static variable definitions
std::vector<Intersection> PathFinder::intersections;
std::vector<std::vector<Road>> PathFinder::graph;
std::vector<Query> PathFinder::queries;
std::vector<Result> PathFinder::results;

void Start()
{
    for (const Query& q : PathFinder::queries)
    {
        Intersection s, d;
        s.x = q.x_s; s.y = q.y_s;
        d.x = q.x_d; d.y = q.y_d;
        vector <Road >SId = FindAdjacentNodes(s, q.R);

        ///*for (int i = 0; i < SId.size(); i++)
        //{
        //    cout << "\nthe source Nodes "<< SId[i].length;
        //}*/

        vector <Road >DId = FindAdjacentNodes(d, q.R);

        ///*for (int i = 0; i < DId.size(); i++)
        //{
        //    cout << "\nthe destination Nodes " << DId[i].length;
        //}*/

        int indx_start = PathFinder::graph.size();
        int indx_end = PathFinder::graph.size() + 1;

        PathFinder::graph.push_back(SId);
        PathFinder::graph.push_back(DId);

        for (int i = 0; i < DId.size(); i++)
        {
            Road r = DId[i];

            int temp = r.neighbor_id;

            r.neighbor_id = indx_end;

            PathFinder::graph[temp].push_back(r);
        }

        Dijkstra(indx_start, indx_end);


        for (int i = 0; i < DId.size(); i++)
        {
            vector<Road>& adj = PathFinder::graph[DId[i].neighbor_id];
            adj.pop_back();

        }


        PathFinder::graph.pop_back(); // indx_end
        PathFinder::graph.pop_back(); // indx_start
    }
}

std::vector<Road> FindAdjacentNodes(const Intersection& point, double R)
{
    vector <Road >nId;
    for (int i = 0; i < PathFinder::intersections.size(); i++)
    {
        double temp = EuclideanDistance(point.x, point.y, PathFinder::intersections[i].x, PathFinder::intersections[i].y);
        if (temp <= R)
        {
            Road r;
            r.neighbor_id = i;
            r.length = temp;
            r.speed = 5;
            r.time = temp / 5 * 60;
            nId.push_back(r);
        }

    }
    return nId;
}

void Dijkstra(int start, int end)
{
    vector<pair<int, int>>parent(PathFinder::graph.size());
    vector<double>times(PathFinder::graph.size(), DBL_MAX);
    times[start] = 0;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;

    pq.push({ 0.0, start });
    while (!pq.empty())
    {
        double curr_time = pq.top().first;
        int curr = pq.top().second;
        pq.pop();

        if (curr == end)
            break;


        if (curr_time > times[curr])
            continue;

        for (int i = 0; i < PathFinder::graph[curr].size(); i++)
        {
            Road r = PathFinder::graph[curr][i];
            double totalTime = times[curr] + r.time;

            if (times[r.neighbor_id] > totalTime)
            {
                times[r.neighbor_id] = totalTime;
                parent[r.neighbor_id] = { curr ,i };
                pq.push({ totalTime, r.neighbor_id });
            }

        }
    }
    //cout << "\ndone\n";
    get_res(parent, start, end, times);

}

void get_res(const std::vector<std::pair<int, int>>& parent, int start, int end, const std::vector<double>& times) {
    Result r;


    int i = end;

    // Collect full path from end to start (including artificial nodes)
    while (i != start) {
        int from_3h = parent[i].first;
        int edgeIndex_3h = parent[i].second;

        if (i != end && i != start) {
            r.pathId.push_back(i);
        }

        r.totalDistance += PathFinder::graph[from_3h][edgeIndex_3h].length;
        i = from_3h;
    }

    r.shortestTime = times[end];

    // Walking distance = the two added links at start and end
    int startEdgeIndex = parent[r.pathId.back()].second;  // edge from 'start' to first real node
    int endFrom = parent[end].first;
    int endEdgeIndex = parent[end].second;



    r.walkingDistance =
        PathFinder::graph[start][startEdgeIndex].length +
        PathFinder::graph[endFrom][endEdgeIndex].length;

    r.vehicleDistance = r.totalDistance - r.walkingDistance;

    PathFinder::results.push_back(r);
}
