/**
 * @author Bhed Kumar Kushwaha
 * @file connecting_points.cpp
 * @version 1.0
 **/
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

using std::priority_queue;
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

/**
 * Function to calculate the total minimum distance required to connect all the
 * points.
 * @param x vector of int containing the x coordinates of the each point.
 * @param y vector of int containing the y coordinates of the each point.
 * @return distance in double datatype.
 **/
double minimum_distance(vector<int> x, vector<int> y) {
    double result = 0.;
    bool isInTree[x.size()]{false};
    priority_queue<city, vector<city>, myComp> pq;
    isInTree[0] = true;
    for (size_t i{1}; i < x.size(); i++) {
        pq.push(city(distance(x[0], x[i], y[0], y[i]), 0, i));
    }
    size_t count_connected{1};
    while (!pq.empty() && count_connected < x.size()) {
        while (isInTree[pq.top().to]) {
            pq.pop();
        }
        auto top = pq.top();
        pq.pop();
        count_connected++;
        result += top.dist;
        isInTree[top.to] = true;
        for (size_t i{}; i < x.size(); i++) {
            if (i != top.to && !isInTree[i]) {
                pq.push(city(distance(x[top.to], x[i], y[top.to], y[i]), top.to,
                             i));
            }
        }
    }

    return result;
}

int main() {
    size_t n;
    std::cin >> n;
    vector<int> x(n), y(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }

    std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
