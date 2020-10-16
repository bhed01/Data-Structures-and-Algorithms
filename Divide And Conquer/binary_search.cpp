/**
 * Implementation of binary search algorithm.
 * @file binary_search.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 */

#include <iostream>
#include <vector>

using std::vector;

/**
 * Finds the index of element in a sorted array.
 * @param a vector of integer containing the sorted elements.
 * @param x interger value to find.
 * @returns index of element if present in vector.
 * @returns -1 if element is not present in vector.
 */
int binary_search(const vector<int> &a, int x) {
    int left = 0, right = (int)a.size() - 1;
    int re;
    bool found = false;
    while (left <= right) {
        int mid{(left + right) / 2};
        if (a.at(mid) == x) {
            found = true;
            re    = mid;
            break;
        } else if (a.at(mid) > x) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    if (found)
        return re;
    else
        return -1;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    int m;
    std::cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i];
    }
    for (int i = 0; i < m; ++i) {
        std::cout << binary_search(a, b[i]) << ' ';
    }
}
