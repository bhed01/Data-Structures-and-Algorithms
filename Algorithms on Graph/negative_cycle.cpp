/**
 * The goal of this program is to implement an algorithm for detected the
 * negative weigth cycle in the graph.
 * @file negative_cycle.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 **/
#include <climits>
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
vector<bool> visited;

/**
 * Function to check whether a vertex is member of the negative weigth cycle or
 * not.
 * @param adj Adjacency matrix of the graph.
 * @param cost Adjacency martrix denoting the weight of the edges.
 * @param s Index of the vertex.
 * @return whether vertex is member of negative weight cycle or not.
 **/
bool search(vector<vector<int>> &adj, vector<vector<int>> &cost, int s) {
    if (!visited[s]) {
        int dst[adj.size()];
        priority_queue<int_pair, vector<int_pair>, std::greater<int_pair>> pq;

        for (int i{}; i < adj.size(); i++) {
            dst[i] = INT_MIN;
        }

        for (int i{}; i < adj[s].size(); i++) {
            int v = adj[s][i];
            pq.push(make_pair(cost[s][i], adj[s][i]));
            dst[v] = cost[s][i];
        }
        visited[s] = true;

        while (!pq.empty()) {
            int_pair top = pq.top();
            pq.pop();
            if (!visited[top.second]) {
                for (int i{}; i < adj[top.second].size(); i++) {
                    int v = adj[top.second][i];
                    int new_dst = cost[top.second][i] + top.first;
                    pq.push(make_pair(new_dst, adj[top.second][i]));

                    if (dst[v] > new_dst || dst[v] == INT_MIN) {
                        dst[v] = new_dst;
                    }
                }
                visited[top.second] = true;
            } else {
                for (int i{}; i < adj[top.second].size(); i++) {
                    int v = adj[top.second][i];
                    int new_dst = cost[top.second][i] + top.first;

                    if (dst[v] > new_dst) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

/**
 * Funtion to check whether a graph contains negative weight cycle or not.
 * @param adj Adjacency matrix of the graph.
 * @param cost Adjacency martrix denoting the weight of the edges.
 * @return whether graph has negative weight cycle or not.
 **/
int negative_cycle(vector<vector<int>> &adj, vector<vector<int>> &cost) {
    visited.resize(adj.size());
    for (int i{}; i < adj.size(); i++) {
        if (search(adj, cost, i)) {
            return 1;
        }
    }
    return 0;
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
    std::cout << negative_cycle(adj, cost);
}
