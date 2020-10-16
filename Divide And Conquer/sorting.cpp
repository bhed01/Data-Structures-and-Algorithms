/**
 *  Implementation of Quick Sort Algorithm.
 *  @file sorting.cpp
 *  @author Bhed Kumar Kushwaha
 *  @version 1.0
 */

#include <cstdlib>
#include <iostream>
#include <vector>

using std::swap;
using std::vector;

/**
 * Partitions the vector.
 * @param a vector of integeres.
 * @param l starting index of array.
 * @param r ending index of array.
 * @param m1
 * @param m2
 */
void partition3(vector<int> &a, int l, int r, int &m1, int &m2) {
    if (r - l <= 1) {
        if (a[r] < a[l]) swap(a[l], a[r]);
        m1 = l;
        m2 = r;
        return;
    }
    int mid{l};
    int pivot{a[r]};
    while (mid <= r) {
        if (a[mid] < pivot)
            swap(a[mid++], a[l++]);
        else if (a[mid] == pivot)
            mid++;
        else
            swap(a[mid], a[r--]);
    }
    m1 = l - 1;
    m2 = mid;
}

/**
 * Sorts the given array using quick sort algorithm.
 * @param a vector of integeres.
 * @param l starting index of array.
 * @param r ending index of array.
 */
void randomized_quick_sort(vector<int> &a, int l, int r) {
    if (l >= r) {
        return;
    }

    int k = l + rand() % (r - l + 1);
    swap(a[l], a[k]);
    int m1{}, m2{};
    partition3(a, l, r, m1, m2);

    randomized_quick_sort(a, l, m1);
    randomized_quick_sort(a, m2, r);
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    randomized_quick_sort(a, 0, a.size() - 1);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << ' ';
    }
}
