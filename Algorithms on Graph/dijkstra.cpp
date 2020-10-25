/**
 * Program to implement the Dijkstra's Algorithm for finding the weight of
 * shortest path between two vertex.
 * @file dijkstra.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 **/

#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using std::make_pair;
using std::priority_queue;
using std::queue;
using std::vector;

typedef std::pair<int, int>
    int_pair;  /// creating new name for pair of int and int.

/**
 * Function to implement the Dijkstra's Algorithm.
 * @param adj Adjacency matrix of the graph.
 * @param cost Adjacency martrix denoting the weight of the edges.
 * @param s Index of the source vertex.
 * @param v Index of the target vertex.
 * @return weight of the shortest path.
 **/
int distance(vector<vector<int>> &adj, vector<vector<int>> &cost, int s,
             int t) {
    int dst[adj.size()]{-1};
    priority_queue<int_pair, vector<int_pair>, std::greater<int_pair>> pq;
    bool visited[adj.size()]{false};

    for (int i{}; i < adj.size(); i++) {
        dst[i] = -1;
    }

    for (int i{}; i < adj[s].size(); i++) {
        int v = adj[s][i];
        pq.push(make_pair(cost[s][i], adj[s][i]));
        dst[v] = cost[s][i];
    }
    visited[s] = true;

    while (!pq.empty()) {
        int_pair top = pq.top();
        if (!visited[top.second]) {
            for (int i{}; i < adj[top.second].size(); i++) {
                int v = adj[top.second][i];
                int new_dst = cost[top.second][i] + top.first;
                pq.push(make_pair(new_dst, adj[top.second][i]));

                if (dst[v] > new_dst || dst[v] == -1) {
                    dst[v] = new_dst;
                }
            }
            visited[top.second] = true;
        }
        pq.pop();
    }
    return dst[t];
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<vector<int>> adj(n, vector<int>());
    vector<vector<int>> cost(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(adj, cost, s, t);
    return 0;
}
