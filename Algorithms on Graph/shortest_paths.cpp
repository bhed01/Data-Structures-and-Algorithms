#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

#define INFINITE std::numeric_limits<long long>::max()

using std::make_pair;
using std::priority_queue;
using std::queue;
using std::vector;

typedef std::pair<long long, int> int_pair;

vector<bool> visit;
void setShortestToFalse(vector<vector<int>> &adj, int ind, vector<bool> &shortest) {
    if (!visit[ind]) {
        visit[ind]    = true;
        shortest[ind] = false;
        for (auto v : adj[ind]) {
            setShortestToFalse(adj, v, shortest);
        }
    }
}

void shortest_paths(vector<vector<int>> &adj, vector<vector<int>> &cost, int s, vector<long long> &distance, vector<bool> &reachable, vector<bool> &shortest) {
    vector<bool> visited(adj.size());
    priority_queue<int_pair, vector<int_pair>, std::greater<int_pair>> pq;

    distance[s]  = 0;
    reachable[s] = true;

    for (int i{}; i < adj[s].size(); i++) {
        int v = adj[s][i];
        pq.push(make_pair(cost[s][i], adj[s][i]));
        distance[v]  = cost[s][i];
        reachable[v] = true;
    }
    visited[s] = true;

    while (!pq.empty()) {
        int_pair top = pq.top();
        pq.pop();
        if (!visited[top.second]) {
            for (int i{}; i < adj[top.second].size(); i++) {
                int v             = adj[top.second][i];
                long long new_dst = cost[top.second][i] + top.first;
                pq.push(make_pair(new_dst, adj[top.second][i]));

                if (distance[v] > new_dst || distance[v] == INFINITE) {
                    distance[v]  = new_dst;
                    reachable[v] = true;
                }
            }
            visited[top.second] = true;
        } else {
            for (int i{}; i < adj[top.second].size(); i++) {
                int v             = adj[top.second][i];
                long long new_dst = cost[top.second][i] + top.first;

                if (distance[v] > new_dst) {
                    visit.clear();
                    visit.resize(adj.size());
                    setShortestToFalse(adj, v, shortest);
                    break;
                }
            }
        }
    }
}

int main() {
    int n, m, s;
    std::cin >> n >> m;
    vector<vector<int>> adj(n, vector<int>());
    vector<vector<int>> cost(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    std::cin >> s;
    s--;
    vector<long long> distance(n, INFINITE);
    vector<bool> reachable(n, false);
    vector<bool> shortest(n, true);
    shortest_paths(adj, cost, s, distance, reachable, shortest);
    for (int i = 0; i < n; i++) {
        if (!reachable[i]) {
            std::cout << "*\n";
        } else if (!shortest[i]) {
            std::cout << "-\n";
        } else {
            std::cout << distance[i] << "\n";
        }
    }
}
