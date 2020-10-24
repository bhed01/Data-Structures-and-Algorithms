/**
 * Program implement an algorithm for checking whether graph is bipartite or
 * not.
 * @file bipartite.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 **/

#include <iostream>
#include <queue>
#include <vector>

using std::queue;
using std::vector;

/**
 * Function to check whether graph is bipartite or not.
 * @param adj Adjacency matrix that represents the graph.
 * @return 1 if graph is bipartite else 0
 **/
int bipartite(vector<vector<int> > &adj) {
    vector<int> group(adj.size(), -1);
    int i = 0;
    while (i < adj.size()) {
        if (group[i] == -1) {
            group[i] = 0;
            queue<int> qu;
            qu.push(i);
            while (!qu.empty()) {
                for (auto v : adj[qu.front()]) {
                    if (group[v] == -1) {
                        group[v] = !group[qu.front()];
                        qu.push(v);
                    } else if (group[v] == group[qu.front()]) {
                        return 0;
                    }
                }
                qu.pop();
            }
        }
        i++;
    }
    return 1;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    std::cout << bipartite(adj);
}
