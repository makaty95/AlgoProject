// #include "PathFinder.h"
// #include "utility.h"
// #include <queue>
// #include <cfloat>
// #include <algorithm>
// #include <iostream>

// // Static variable definitions
// //std::vector<DS::Node> PathFinder::intersections;
// //std::vector<std::vector<DS::Edge>> PathFinder::graph;
// using namespace std;

// void Start()
// {
//     // clearing for new results.
//     MapData::results.clear();

//     for (const DS::Query& q : MapData::queries)
//     {
//         DS::Node s, d;
//         s.loc.x = q.S.x; s.loc.y = q.S.y;
//         d.loc.x = q.E.x; d.loc.y = q.E.y;

//         vector <DS::Edge >SId = FindAdjacentNodes(s, q.R);

//         ///*for (int i = 0; i < SId.size(); i++)
//         //{
//         //    cout << "\nthe source Nodes "<< SId[i].length;
//         //}*/

//         vector <DS::Edge >DId = FindAdjacentNodes(d, q.R);

//         ///*for (int i = 0; i < DId.size(); i++)
//         //{
//         //    cout << "\nthe destination Nodes " << DId[i].length;
//         //}*/

//         int indx_start = MapData::graph.size();
//         int indx_end = MapData::graph.size() + 1;

//         MapData::graph.push_back(SId);
//         MapData::graph.push_back(DId);

//         for (int i = 0; i < DId.size(); i++)
//         {
//             DS::Edge r = DId[i];

//             int temp = r.neighbor_id;

//             r.neighbor_id = indx_end;

//             MapData::graph[temp].push_back(r);
//         }

//         Dijkstra(indx_start, indx_end);


//         for (int i = 0; i < DId.size(); i++)
//         {
//             vector<DS::Edge>& adj = MapData::graph[DId[i].neighbor_id];
//             adj.pop_back();

//         }


//         MapData::graph.pop_back(); // indx_end
//         MapData::graph.pop_back(); // indx_start
//     }
// }

// std::vector<DS::Edge> FindAdjacentNodes(const DS::Node& point, double R)
// {
//     vector <DS::Edge >nId;
//     for (int i = 0; i < MapData::nodes.size(); i++)
//     {
        
//         double temp = Geometry::EuclideanDistance(point.loc, MapData::nodes[i].loc);
//         if (temp <= R)
//         {
//             DS::Edge r;
//             r.neighbor_id = i;
//             r.length = temp;
//             r.speed = 5;
//             r.time = temp / 5 * 60;
//             nId.push_back(r);
//         }

//     }
//     return nId;
// }

// void Dijkstra(int start, int end)
// {
//     vector<pair<int, int>>parent(MapData::graph.size());
//     vector<double>times(MapData::graph.size(), DBL_MAX);
//     times[start] = 0;
//     priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;

//     pq.push({ 0.0, start });
//     while (!pq.empty())
//     {
//         double curr_time = pq.top().first;
//         int curr = pq.top().second;
//         pq.pop();

//         if (curr == end)
//             break;


//         if (curr_time > times[curr])
//             continue;

//         for (int i = 0; i < MapData::graph[curr].size(); i++)
//         {
//             DS::Edge r = MapData::graph[curr][i];
//             double totalTime = times[curr] + r.time;

//             if (times[r.neighbor_id] > totalTime)
//             {
//                 times[r.neighbor_id] = totalTime;
//                 parent[r.neighbor_id] = { curr ,i };
//                 pq.push({ totalTime, r.neighbor_id });
//             }

//         }
//     }
//     //cout << "\ndone\n";
//     get_res(parent, start, end, times);

// }

// void get_res(const std::vector<std::pair<int, int>>& parent, int start, int end, const std::vector<double>& times) {
//     Result r;


//     int i = end;

//     // Collect full path from end to start (including artificial nodes)
//     while (i != start) {
//         int from_3h = parent[i].first;
//         int edgeIndex_3h = parent[i].second;

//         if (i != end && i != start) {
//             r.pathId.push_back(i);
//         }

//         r.totalDistance += MapData::graph[from_3h][edgeIndex_3h].length;
//         i = from_3h;
//     }

//     r.shortestTime = times[end];

//     // Walking distance = the two added links at start and end
//     int startEdgeIndex = parent[r.pathId.back()].second;  // edge from 'start' to first real node
//     int endFrom = parent[end].first;
//     int endEdgeIndex = parent[end].second;



//     r.walkingDistance =
//         MapData::graph[start][startEdgeIndex].length +
//         MapData::graph[endFrom][endEdgeIndex].length;

//     r.vehicleDistance = r.totalDistance - r.walkingDistance;

//     MapData::results.push_back(r);
// }




#include "PathFinder.h"
#include "utility.h"
#include <queue>
#include <cfloat>
#include <algorithm>
#include <iostream>
#include <functional>

// Static variable definitions
//std::vector<DS::Node> PathFinder::intersections;
//std::vector<std::vector<DS::Edge>> PathFinder::graph;
using namespace std;

///////////////////////
struct KDNode {
    int index; // index of intersection in PathFinder::intersections
    KDNode* left = nullptr;
    KDNode* right = nullptr;
    bool verticalSplit; // true = split by x, false = split by y

    KDNode(int idx, bool split) : index(idx), verticalSplit(split) {}
};

class KDTree {
private:
    KDNode* root = nullptr;

    KDNode* build(std::vector<int>& points, int depth) {
        if (points.empty( )) return nullptr;
        bool vertical = (depth % 2 == 0);

        auto comparator = [&](int lhs, int rhs) {
            if (vertical)
                return MapData::nodes[lhs].loc.x < MapData::nodes[rhs].loc.x;
            else
                return  MapData::nodes[lhs].loc.y < MapData::nodes[rhs].loc.y;
            };

        int mid = points.size() / 2;
        std::nth_element(points.begin(), points.begin() + mid, points.end(), comparator);

        KDNode* node = new KDNode(points[mid], vertical);

        std::vector<int> leftPoints(points.begin(), points.begin() + mid);
        std::vector<int> rightPoints(points.begin() + mid + 1, points.end());

        node->left = build(leftPoints, depth + 1);
        node->right = build(rightPoints, depth + 1);

        return node;
    }

    void radiusSearchRec(KDNode* node, const DS::Node& point, double radius, std::vector<int>& result) const {
        if (!node) return;

        const DS::Node& curr = MapData::nodes[node->index];
        double dist = std::sqrt(std::pow(curr.loc.x - point.loc.x, 2) + std::pow(curr.loc.y - point.loc.y, 2));

        if (dist <= radius)
            result.push_back(node->index);

        bool vertical = node->verticalSplit;
        double delta = vertical ? point.loc.x - curr.loc.x : point.loc.y - curr.loc.y;

        if (delta < 0) {
            radiusSearchRec(node->left, point, radius, result);
            if (std::abs(delta) <= radius)
                radiusSearchRec(node->right, point, radius, result);
        }
        else {
            radiusSearchRec(node->right, point, radius, result);
            if (std::abs(delta) <= radius)
                radiusSearchRec(node->left, point, radius, result);
        }
    }

public:
    void build(const std::vector<DS::Node>& intersections) {
        std::vector<int> points(intersections.size());
        for (int i = 0; i < (int)intersections.size(); i++)
            points[i] = i;

        root = build(points, 0);
    }

    std::vector<int> radiusSearch(const DS::Node& point, double radius) const {
        std::vector<int> result;
        radiusSearchRec(root, point, radius, result);
        return result;
    }

    ~KDTree() {
        std::function<void(KDNode*)> cleanup = [&](KDNode* node) {
            if (!node) return;
            cleanup(node->left);
            cleanup(node->right);
            delete node;
            };
        cleanup(root);
    }
};

static KDTree kdtree;

void PathFinder::InitializeKDTree() {
    kdtree.build(MapData::nodes);
}



/////////////////////////////

void Start()
{
    // clearing for new results.
    MapData::results.clear();
    PathFinder::InitializeKDTree();
   

    for (const DS::Query& q : MapData::queries)
    {
        DS::Node s, d;
        s.loc.x = q.S.x; s.loc.y = q.S.y;
        d.loc.x = q.E.x; d.loc.y = q.E.y;

        vector <DS::Edge >SId = FindAdjacentNodes(s, q.R);

        ///*for (int i = 0; i < SId.size(); i++)
        //{
        //    cout << "\nthe source Nodes "<< SId[i].length;
        //}*/

        vector <DS::Edge >DId = FindAdjacentNodes(d, q.R);

        ///*for (int i = 0; i < DId.size(); i++)
        //{
        //    cout << "\nthe destination Nodes " << DId[i].length;
        //}*/

        int indx_start = MapData::graph.size();
        int indx_end = MapData::graph.size() + 1;

        MapData::graph.push_back(SId);
        MapData::graph.push_back(DId);

        for (int i = 0; i < DId.size(); i++)
        {
            DS::Edge r = DId[i];

            int temp = r.neighbor_id;

            r.neighbor_id = indx_end;

            MapData::graph[temp].push_back(r);
        }

        Dijkstra(indx_start, indx_end);


        for (int i = 0; i < DId.size(); i++)
        {
            vector<DS::Edge>& adj = MapData::graph[DId[i].neighbor_id];
            adj.pop_back();

        }


        MapData::graph.pop_back(); // indx_end
        MapData::graph.pop_back(); // indx_start
    }
}

//std::vector<DS::Edge> FindAdjacentNodes(const DS::Node& point, double R)
//{
//    vector <DS::Edge >nId;
//    for (int i = 0; i < MapData::nodes.size(); i++)
//    {
//        
//        double temp = Geometry::EuclideanDistance(point.loc, MapData::nodes[i].loc);
//        if (temp <= R)
//        {
//            DS::Edge r;
//            r.neighbor_id = i;
//            r.length = temp;
//            r.speed = 5;
//            r.time = temp / 5 * 60;
//            nId.push_back(r);
//        }
//
//    }
//    return nId;
//}

void Dijkstra(int start, int end)
{
    vector<pair<int, int>>parent(MapData::graph.size());
    vector<double>times(MapData::graph.size(), DBL_MAX);
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

        for (int i = 0; i < MapData::graph[curr].size(); i++)
        {
            DS::Edge r = MapData::graph[curr][i];
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

        r.totalDistance += MapData::graph[from_3h][edgeIndex_3h].length;
        i = from_3h;
    }

    r.shortestTime = times[end];

    // Walking distance = the two added links at start and end
    int startEdgeIndex = parent[r.pathId.back()].second;  // edge from 'start' to first real node
    int endFrom = parent[end].first;
    int endEdgeIndex = parent[end].second;



    r.walkingDistance =
        MapData::graph[start][startEdgeIndex].length +
        MapData::graph[endFrom][endEdgeIndex].length;

    r.vehicleDistance = r.totalDistance - r.walkingDistance;

    MapData::results.push_back(r);
}






std::vector<DS::Edge> FindAdjacentNodes(const DS::Node& point, double R)
{
    std::vector<DS::Edge> nId;

    // Use KD-tree radius search
    std::vector<int> neighbors = kdtree.radiusSearch(point, R);

    for (int idx : neighbors)
    {
        double temp = Geometry::EuclideanDistance(point.loc, MapData::nodes[idx].loc);
        DS::Edge r;
        r.neighbor_id = idx;
        r.length = temp;
        r.speed = 5;
        r.time = temp / 5 * 60;
        nId.push_back(r);
    }
    return nId;
}
