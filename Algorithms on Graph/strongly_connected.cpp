/**
 * The program to implement an algorithm for computation of number of strongly
 *connected components in a graph.
 * @file strongly_connected.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 **/
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using std::pair;
using std::stack;
using std::vector;

/**
 * Function to compute the reverse directed graph from a directed graph.
 * @param adj Adjacency matrix that represents the graph.
 * @return Ajdacency matrix of reversed graph.
 **/
vector<vector<int> > reverseEdges(vector<vector<int> > &adj) {
    vector<vector<int> > rAdj(adj.size(), vector<int>());
    for (int i = 0; i < adj.size(); i++) {
        for (int j = 0; j < adj[i].size(); j++) {
            rAdj[adj[i][j]].push_back(i);
        }
    }
    return rAdj;
}

/**
 * Function for DFS of a graph.
 * @param adj Adjacency matrix that represents the graph.
 * @param x Index of the current vertex.
 * @param visited vector to store visited vertex value.
 * @param stack stack for storing the order of traversal.
 **/
void dfs(vector<vector<int> > &adj, int x, vector<int> &visited,
         stack<int> &Stack) {
    visited[x] = 1;

    for (int i = 0; i < adj[x].size(); i++) {
        if (!visited[adj[x][i]]) {
            visited[adj[x][i]] = 1;
            dfs(adj, adj[x][i], visited, Stack);
        }
    }
    Stack.push(x);
}

/**
 * Function to compute the number of strongly connected components in the graph.
 * @param adj Adjacency matrix that represents the graph.
 * @return number of strongly connected components.
 **/
int number_of_strongly_connected_components(vector<vector<int> > adj) {
    int result = 0;
    stack<int> Stack;

    vector<int> visited(adj.size(), 0);

    for (int i = 0; i < adj.size(); i++) {
        if (!visited[i]) {
            dfs(adj, i, visited, Stack);
        }
    }

    vector<vector<int> > rAdj = reverseEdges(adj);

    for (int i = 0; i < adj.size(); i++) {
        visited[i] = 0;
    }

    while (!Stack.empty()) {
        int x = Stack.top();
        Stack.pop();

        if (!visited[x]) {
            stack<int> componentStack;
            dfs(rAdj, x, visited, componentStack);
            result++;
        }
    }
    return result;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
    }
    std::cout << number_of_strongly_connected_components(adj);
}