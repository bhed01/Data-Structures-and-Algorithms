/**
 * @author Bhed Kumar Kushwaha
 * @file clustering.cpp
 * @version 1.0
 **/
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

using std::pair;
using std::vector;

struct city {
    double dist;
    int from, to;
    city(double dist, int from, int to) : dist(dist), from(from), to(to) {}
};

struct myComp {
    bool operator()(city const& a, city const& b) { return a.dist > b.dist; }
};

/**
 * Class for implementing the functionality of a disjoint set.
 **/
class DisjointSet {
    vector<int> parent, rank;
    int size;

    /**
     * Function to initialize the set
     **/
    void makeset() {
        for (int i{}; i < size; i++) {
            parent[i] = i;
        }
    }

   public:
    DisjointSet(int n) : size(n) {
        parent.resize(n);
        rank.resize(n, 0);
        makeset();
    }

    /**
     * function to find the parent of the node.
     * @param x Index of the node.
     * @return Index of the parent of the node.
     **/
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    /**
     * Function to merge two sets.
     * @param u Index of node of first set.
     * @param v Index of node of second set.
     * @return true if merged else false.
     **/
    bool Union(int u, int v) {
        int uid = find(u), vid = find(v);
        if (uid != vid) {
            if (rank[uid] > rank[vid]) {
                parent[vid] = uid;
            } else {
                parent[uid] = vid;
                if (rank[uid] == rank[vid]) rank[vid]++;
            }
            return true;
        }
        return false;
    }
};

/**
 * Fuction to calculate the distance between two points in xy plane.
 * @param x1 x coordinate of first point
 * @param x2 x coordinate of second point
 * @param y1 y coordinate of first point
 * @param y2 y coordinate of second point
 * @return ditance between points in double datatype.
 **/
double distance(int x1, int x2, int y1, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double clustering(vector<int> x, vector<int> y, int k) {
    int clusters = x.size();
    DisjointSet A(x.size());
    std::priority_queue<city, vector<city>, myComp> pq;
    for (int i{}; i < x.size() - 1; i++) {
        for (int j{i + 1}; j < x.size(); j++) {
            pq.push(city(distance(x[i], x[j], y[i], y[j]), i, j));
        }
    }
    while (clusters > k) {
        auto top = pq.top();
        pq.pop();
        while (!A.Union(top.from, top.to)) {
            top = pq.top();
            pq.pop();
        }
        clusters--;
    }
    while (!A.Union(pq.top().from, pq.top().to)) {
        pq.pop();
    }
    return pq.top().dist;
}

int main() {
    size_t n;
    int k;
    std::cin >> n;
    vector<int> x(n), y(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }
    std::cin >> k;
    std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
