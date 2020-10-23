/**
 * The goal of the program is to implement an algorithm to check whether a given
 * directed graph is cyclic.
 * @file acyclicity.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 **/
#include <iostream>
#include <unordered_set>
#include <vector>

using std::pair;
using std::vector;

std::unordered_set<int> removed;
std::unordered_set<int> visited;

/**
 * Function to check whether a vertex contibutes in the formation of a cycle.
 * @param adj Adjacency matrix that represents the graph.
 * @param ind Index of the vertex.
 * @return true if vertex doesn't form a cycle else false.
 **/
bool isAcyclic(vector<vector<int>> &adj, size_t ind) {
    if (removed.find(ind) == removed.end()) {
        if (visited.find(ind) == visited.end()) {
            visited.insert(ind);
            for (auto v : adj[ind]) {
                if (!isAcyclic(adj, v)) return false;
            }
            removed.insert(ind);
            return true;
        } else {
            return false;
        }
    } else {
        return true;
    }
}

/**
 * Function to check whether a graph is acyclic or not.
 * @param adj Adjacency matrix that represents the graph.
 * @return 1 if graph is acyclic else 0.
 **/
int acyclic(vector<vector<int>> &adj) {
    for (size_t i{}; i < adj.size(); i++) {
        if (!isAcyclic(adj, i)) return 1;
    }
    return 0;
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
    std::cout << acyclic(adj);
}
