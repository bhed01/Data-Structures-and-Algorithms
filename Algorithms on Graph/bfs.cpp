/**
 * The goal of this program is to implement an algorithm to compute shortest
 * path between to vertex in the graph.
 * @file bfs.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 **/

#include <iostream>
#include <queue>
#include <vector>

using std::queue;
using std::vector;

/**
 * Funtion to compute shortest path between two vertex in graph using BFS.
 * @param adj Adjacency matrix that represents the graph.
 * @param s Index of the source vertex.
 * @param t Index of destination vertex.
 * @return number of edges in shortest path if exists else -1.
 **/
int distance(vector<vector<int>> &adj, int s, int t) {
    vector<int> dist(adj.size(), -1);
    dist[s] = 0;
    queue<int> qu;
    qu.push(s);
    while (!qu.empty()) {
        for (auto v : adj[qu.front()]) {
            if (dist[v] == -1) {
                if (v == t) {
                    return dist[qu.front()] + 1;
                }
                dist[v] = dist[qu.front()] + 1;
                qu.push(v);
            }
        }
        qu.pop();
    }
    return -1;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<vector<int>> adj(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(adj, s, t);
}
