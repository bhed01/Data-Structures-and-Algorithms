/**
 * The goal of this program is to implement an algorithm to compute a
 * topological ordering of directed acyclic graph.
 * @file toposort.cpp
 * @author Bhed Kumar Kushwah
 * @version 1.0
 **/
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using std::pair;
using std::vector;

std::unordered_set<int> removed;

/**
 * Function for DFS of a graph.
 * @param adj Adjacency matrix that represents the graph.
 * @param order To store the order of the search.
 * @param ind Index of the vertex.
 **/
void dfs(vector<vector<int>> &adj, vector<int> &order, size_t ind) {
    if (removed.find(ind) == removed.end()) {
        for (auto v : adj[ind]) {
            dfs(adj, order, v);
        }
        removed.insert(ind);
        order.push_back(ind);
    }
}

/**
 * Function to compute the topological ordering of graph.
 * @param adj Adjacency matrix that represents the graph.
 * @return vector of topological ordering.
 **/
vector<int> toposort(vector<vector<int>> &adj) {
    vector<int> order;
    for (size_t i{}; i < adj.size(); i++) {
        dfs(adj, order, i);
    }
    return order;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int>> adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
    }
    vector<int> order = toposort(adj);
    for (long long i = (long long)order.size() - 1; i >= 0; i--) {
        std::cout << order[i] + 1 << " ";
    }
}
