/**
 * Implementation of an algorithm to find minimum distance between
   two closest point in the given set of points.
 * @file closest.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 */

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::min;
using std::pair;
using std::string;
using std::vector;

/**
 * Naive Algorithm to find minimum distance between closest points.
 * @param points vector of points.
 * @param left starting index of vector.
 * @param right ending index of vector.
 * @returns double value denoting minimum distance.
 */
double minimal_distance_naive(const vector<pair<int, int>> &points, int left,
                              int right) {
    double d{FLT_MAX};
    for (int i{left}; i < right; i++) {
        for (int j{i + 1}; j <= right; j++) {
            if (i != j)
                d = min(d,
                        hypot((double)(points[i].first - points[j].first),
                              (double)(points[i].second - points[j].second)));
        }
    }
    return d;
}

/**
 * Finds the minimum distance between closest points.
 * @param points vector of points.
 * @param left starting index of vector.
 * @param right ending index of vector.
 * @returns double value denoting minimum distance.
 */
double minimal_distance(const vector<pair<int, int>> &points, int left,
                        int right) {
    if (left + 2 >= right) {
        return minimal_distance_naive(points, left, right);
    }
    int mid{left + (right - left) / 2};
    double d{min(minimal_distance(points, left, mid),
                 minimal_distance(points, mid + 1, right))};
    vector<pair<int, int>> temp;
    int delta{(int)d + 1};
    int x{points[mid].first};
    for (int i{left}; i <= right; i++) {
        if (abs(points[i].first - x) <= delta)
            temp.push_back(std::make_pair(points[i].first, points[i].second));
    }
    std::sort(temp.begin(), temp.end(), [&](const auto &i, const auto &j) {
        return i.second < j.second;
    });
    for (int i{}; i < temp.size(); i++) {
        for (int j{i + 1}; (j < i + 8) && (j < temp.size()); j++) {
            double dist{hypot((double)(temp[i].first - temp[j].first),
                              (double)(temp[i].second - temp[j].second))};
            d = min(d, dist);
        }
    }
    return d;
}

int main() {
    size_t n;
    std::cin >> n;
    vector<pair<int, int>> points(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> points[i].first >> points[i].second;
    }
    std::sort(points.begin(), points.end(),
              [&](const auto &i, const auto &j) { return i.first < j.first; });
    std::cout << std::fixed;
    std::cout << std::setprecision(9)
              << minimal_distance(points, 0, (int)points.size() - 1) << "\n";
}
