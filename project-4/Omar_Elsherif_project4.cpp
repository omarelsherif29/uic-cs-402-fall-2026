
// be sure to change FIRSTNAME and LASTNAME with your own first and last name
#include "Omar_Elsherif_project4.h"
#include <string>
#include <queue>
#include <tuple>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;

const string who_am_i() {
    return "Omar_Elsherif";
}

/****************
 * INSTRUCTIONS *
 ****************
 *
 * - Replace all instances of "Firstname_Lastname" with your firstname and
 *   your last name. This include the .h and .cpp files, along with the
 *   header guards at the top of the .h file.
 *
 * - Implement the appropriate algorithms as described below.
 *   You must follow the specifications as written below.
 *
 * - Certain function signatures may not be modified (as it will affect auto
 *   grading). These functions will be specified.
 *
 * - You are allowed to add helper functions. Be sure to add the appropriate
 *   function prototypes in "Fistname_Lastname_project4.h."
 *
 * - The file "testing.cpp" has various functions you can utilize to test
 *   your code. You can also add your own tests!
 *
 * - If you are working in a group, please modify the comments directly below.
 *   
 * - IMPORTANT: If you are working in a group, every member is expected to submit their
 *   source code individually.
 *
 */



/*** PROJECT 4: Graphs ***/

/* Topological Sorting
 *
 * 10 Points
 *
 * In this problem, you are tasked with reading the description of a
 * directed graph as input, then outputting a valid topological
 * sort of the graph, if one exists.
 *
 * Input
 *  - int n: number of nodes/vertices in the graph, labeled from 0 to n-1
 *  - vector<Edge> edges: a list of directed edges in the graph
 *
 * Output
 *  - vector<int>: a valid topological sorting of the graph. If
 *    no topological sorting exists, output an empty list.
 *    If multiple topological sortings exist, you only need to
 *    output a single one.
 *
 * Note: Edge is a struct defined in Firstname_Lastname_project2.h.
 *
 */
vector<int> topological_sort(int n, vector<Edge> edges) {
    vector<vector<int>> graph(n);
    vector<int> indeg(n, 0);
    for (const Edge& e : edges) {
        graph[e.from].push_back(e.to);
        ++indeg[e.to];
    }

    queue<int> q;
    for (int i = 0; i < n; ++i)
        if (indeg[i] == 0) q.push(i);

    vector<int> order;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : graph[u])
            if (--indeg[v] == 0) q.push(v);
    }

    if ((int)order.size() != n) return {};
    return order;
}


/* Single Source Shortest Paths on DAGs
 *
 * 15 points
 *
 * In this problem, you will be given a directed acyclic graph with 
 * arbitrary integer edge weights (i.e., they can be negative!), as
 * well as a single source node. Your goal will be to output the
 * shortest distance from the source to every other vertex in the
 * graph.
 *
 * Input
 *  - int n: number of nodes in the graph, labeled from 0 to n-1
 *  - vector<Edge> edges: list of weighted directed edges in the graph
 *  - int source: ID of the source node
 *
 * Output
 *  - vector<int>: vector of size n such that entry i is the distance
 *    from source to i in the given graph. Use the value "INT_MAX" to
 *    indicate that there is no path from source to i.
 *
 * Algorithm
 *  - Topological Sorting + BFS is enough to solve this problem.
 *
 * Assumptions
 *  - The graph given as input will always be a DAG
 *
 */
vector<int> dag_single_source(int n, vector<Edge> edges, int source) {
    if (n <= 0) return {};
    vector<int> dist(n, INT_MAX);
    if (source < 0 || source >= n) return dist;

    vector<vector<pair<int,int>>> graph(n);
    for (const Edge& e : edges)
        graph[e.from].push_back({e.to, e.weight});

    vector<int> order = topological_sort(n, edges);
    dist[source] = 0;

    for (int u : order) {
        if (dist[u] == INT_MAX) continue;
        for (auto [v, w] : graph[u])
            if (dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
    }
    return dist;
}


/* Dijkstra's Algorithm
 *
 * 25 Points
 *
 * In this problem, you are simply tasked to implement Dijkstra's Algorithm.
 *
 * Input
 *  - int n: number of nodes in the graph, labeled from 0 to n-1
 *  - vector<Edge> edges: list of weighted directed edges in the graph
 *  - int source: ID of the source node
 *
 * Output
 *  - vector<Node>: a list of size n such that entry i contains a Node node
 *    with the following properties:
 *      - node.id = i
 *      - node.path_cost = cost of the shortest path from source to i
 *      - node.pred = id of the predecessor of i on the shortest path from
 *        source to i
 *
 * Assumptions
 *  - You are guaranteed that the graph contains only non-negative edges
 *    (i.e., weight at least 0). For simplicity, all weights will be
 *    integers.
 * 
 * Note: Node is a struct defined in Firstname_Lastname_project2.h.
 */


vector<Node> dijkstras_algorithm(int n, vector<Edge> edges, int source) {
    // Note: see the LeetCode from in-class for the problem "Cheapest Flights
    // K stops" to see how you can create a priority_queue with the Node struct.
    if (n <= 0) return {};

    vector<Node> best(n);
    for (int i = 0; i < n; ++i) best[i] = {i, INT_MAX, -1};
    if (source < 0 || source >= n) return best;

    vector<vector<pair<int,int>>> graph(n);
    for (const Edge& e : edges)
        graph[e.from].push_back({e.to, e.weight});

    best[source].path_cost = 0;

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push(best[source]);

    while (!pq.empty()) {
        Node u = pq.top(); pq.pop();
        if (u.path_cost > best[u.id].path_cost) continue;

        for (auto [v, w] : graph[u.id]) {
            if (u.path_cost != INT_MAX && u.path_cost + w < best[v].path_cost) {
                best[v].path_cost = u.path_cost + w;
                best[v].pred = u.id;
                pq.push(best[v]);
            }
        }
    }
    return best; 
}


/* A-star Algorithm
 *
 * 25 Points
 *
 * In this problem, you are asked to implement a modified version of Dijkstras,
 * known as A* (A-star). The A* algorithm is very similar to Dijkstras, with
 * two notable differences:
 *  (a) A* uses some heuristic function h to estimate the distance between any
 *      two nodes; and
 *  (b) A* only finds a path from a specified source node and a target node.
 *
 * Recall in Dijkstras, the algorithm finds the shortest path from a single
 * source to all other nodes in the graph.
 *
 * Given a source s and a target t, A* is guaranteed to output a shortest path
 * from s to t as long as the heuristic h underestimates the distance between 
 * any two nodes u,v in the graph. If d(u,v) represents the actual distance
 * between u and v, then h(u,v) <= d(u,v) for all u,v is enough to guarantee
 * that A* outputs a shortest path from s to t.
 *
 * For this specific version of A*, you will be given two points on a grid (a
 * start point and an end point). The grid will be specified by a graph, with
 * nodes being a GridNode (each with their own x and y value on the grid), and
 * edges being a GridEdge. Each GridEdge has a weight that is of a double type.
 * A GridEdge will only connect adjacent or diagonal nodes. Formally, for a
 * GridNode at point (x,y), all of the following edges are possible:
 *
 *  - (x+1, y) (cost = 1.0)
 *  - (x-1, y) (cost = 1.0)
 *  - (x, y+1) (cost = 1.0)
 *  - (x, y-1) (cost = 1.0)
 *  - (x+1, y+1) (cost = 1.5)
 *  - (x-1, y+1) (cost = 1.5)
 *  - (x+1, y-1) (cost = 1.5)
 *  - (x-1, y-1) (cost = 1.5)
 * 
 * Here, edges all have an implicit movement cost, described above. Moving along
 * a diagonal edge has a cost of 1.5, while moving along a cardinally adjacent  
 * edge (north, south, east, west) has a cost of 1.
 *
 * Note that GridEdge and GridNode are structs defined in Firstname_Lastname_project2.h.
 *
 * Input:
 *  - int m: number of columns (x-axis)
 *  - int n: number of rows in the grid (y-axis)
 *  - vector<GridEdge> edges: list of edges in the graph
 *  - GridNode source: source node of the algorithm
 *  - GridNode target: target node of the algorithm
 *  - function<double(GridNode, GridNode)> h: h is a function which takes as input
 *      two GridNodes and outputs a double. This represents the heruistic_cost
 *      function for A*.
 *
 * Output:
 *  - vector<GridNode>: a list of nodes containing the path from source to target.
 *                      Note that if variable "output" is your output vector, then
 *                      it must satisfy the following properties:
 *                          - if a path from source to target exists, then
 *                              - output[0] = source
 *                              - output[output.size()-1] = target
 *                              - Moreover, output[output.size()-1].path_cost is the cost
 *                                of the path from source to target.
 *                          - if no path from source to target exists, then
 *                              - output = {} (the empty list)
 *
 * Algorithm:
 *  The algorithm is nearly identical to Dijkstra's Algorithm, with the following changes.
 *      - Suppose in Dijkstra's you are currently considering node u and expanding the 
 *        frontier along the neighbors of u.
 *      - Let v be a neighbor of u.
 *      - In Dijkstra's, you check if u.cost + weight(u,v) < v.cost, where weight(u,v) 
 *        is the weight of the edge from u to v. If this is true, you update v.cost as
 *        v.cost = u.cost + weight(u,v), update it in / add it to the priority queue,
 *        and continue.
 *      - In A*, this is modified as: v.cost = u.cost + weight(u,v) + heuristic_cost(v, target),
 *        where heuristic_cost(v, target) is a heuristic distance from node v to the target node
 *        target.
 *          - Note you also change the dijkstra's check to u.cost+weight(u,v)+heuristic_cost(v,target) < v.cost
 *  
 *  As part of your implementation of A*, you are required to implement the function
 *  heuristic_cost(GridNode start, GridNode dest) defined below. Your heuristic should never
 *  over estimate the distance between any two nodes start and dest. Remember, in theory you
 *  can move north, south, east, west, or along any diagonal (so long as there is an edge).
 *  Use this information to write a heuristic function that never over estimates the distance.
 *
 *
 * Additional Resources:
 *  - Wikipedia: https://en.wikipedia.org/wiki/A*_search_algorithm
 *  - GeeksForGeeks: https://www.geeksforgeeks.org/dsa/a-search-algorithm/
 *  - Stanford: https://theory.stanford.edu/~amitp/GameProgramming/AStarComparison.html
 *
 */



// You must implement this function.
double heuristic_cost(GridNode start, GridNode dest) {
    double dx = abs(start.x - dest.x);
    double dy = abs(start.y - dest.y);
    double diag = min(dx, dy);
    double straight = max(dx, dy) - diag;
    return 1.5 * diag + straight;
}

// To test your algorithm with the function "heruistic_cost" above,
// simply pass "heuristic_cost" as a parameter to the function.
vector<GridNode> a_star_algorithm(
    int m, 
    int n, 
    vector<GridEdge> edges, 
    GridNode source, 
    GridNode target,
    function<double(GridNode,GridNode)> h
) 
{
    if (m <= 0 || n <= 0) return {};

    auto in_bounds = [&](int x, int y) { return x >= 0 && x < m && y >= 0 && y < n; };
    auto id = [&](int x, int y) { return y * m + x; };

    if (!in_bounds(source.x, source.y) || !in_bounds(target.x, target.y)) return {};

    vector<vector<pair<int,double>>> adj(m * n);
    for (const GridEdge& e : edges) {
        if (!in_bounds(e.from_x, e.from_y) || !in_bounds(e.to_x, e.to_y)) continue;
        bool diagonal = (e.from_x != e.to_x) && (e.from_y != e.to_y);
        adj[id(e.from_x, e.from_y)].push_back({id(e.to_x, e.to_y), diagonal ? 1.5 : 1.0});
    }

    const double INF = numeric_limits<double>::infinity();
    vector<GridNode> best(m * n);
    for (int y = 0; y < n; ++y)
        for (int x = 0; x < m; ++x)
            best[id(x, y)] = {x, y, INF, -1, -1};

    int s = id(source.x, source.y);
    int t = id(target.x, target.y);
    best[s].path_cost = 0.0;
    
    // queue entries: (f = g + h, g, node id), min-heap on f.
    // path_cost stores the true cost g so the output matches the spec
    // f is used only for ordering the priority queue.
    using Entry = tuple<double,double,int>;
    priority_queue<Entry, vector<Entry>, greater<Entry>> pq;
    pq.push({h(best[s], target), 0.0, s});

    while (!pq.empty()) {
        auto [f, g, u] = pq.top(); pq.pop();
        if (g > best[u].path_cost) continue;
        if (u == t) break;

        for (auto [v, w] : adj[u]) {
            double ng = g + w;
            if (ng < best[v].path_cost) {
                best[v].path_cost = ng;
                best[v].pred_x = best[u].x;
                best[v].pred_y = best[u].y;
                pq.push({ng + h(best[v], target), ng, v});
            }
        }
    }

    if (best[t].path_cost == INF) return {};

    vector<GridNode> path;
    int cur = t;
    while (true) {
        path.push_back(best[cur]);
        if (cur == s) break;
        cur = id(best[cur].pred_x, best[cur].pred_y);
    }
    reverse(path.begin(), path.end());
    return path;
}
