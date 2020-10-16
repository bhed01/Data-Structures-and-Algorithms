/**
 * Given a set of points on a line and a set of segments on a line. The goal is
   to compute, for each point, the number of segments that contain this point.
 * @file points_and_segments.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 */

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

using std::pair;
using std::unordered_map;
using std::vector;

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<pair<int, char>> all(n + n + m);

    for (size_t i = 0; i < n; i++) {
        std::cin >> all[i].first >> all[n + i].first;
        all[i].second     = 'l';
        all[n + i].second = 'r';
    }
    vector<int> points(m);
    for (size_t i = 0; i < m; i++) {
        std::cin >> points[i];
        all[n + n + i].first  = points[i];
        all[n + n + i].second = 'p';
    }

    std::sort(all.begin(), all.end(), [](const auto &i, const auto &j) {
        if (i.first == j.first) {
            if (i.second == 'p' && j.second == 'l')
                return false;
            else if (i.second == 'r' && j.second == 'p')
                return false;
            else if (i.second == 'r' && j.second == 'l')
                return false;
            return true;
        }
        return i.first < j.first;
    });

    int count{};
    unordered_map<int, int> result;
    for (auto e : all) {
        if (e.second == 'l') {
            count++;
        } else if (e.second == 'p') {
            result[e.first] = count;
        } else {
            count--;
        }
    }

    for (size_t i = 0; i < m; i++) {
        std::cout << result[points[i]] << ' ';
    }
}
