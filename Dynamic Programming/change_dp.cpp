/**
 * The goal of this problem is to implement the algorithm for finding the
 * minimum number of coins with denominations 1, 3, 4 that changes money.
 * @file change_dp.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 */
#include <iostream>
#include <vector>

using std::vector;

/**
 * Finds the minumum of three interger
 * @param x integer.
 * @param y integer.
 * @param z integer.
 * @returns minimum out of x, y and z.
 */
int min(int x, int y, int z) {
    return (x < y) ? ((x < z) ? x : z) : ((y < z) ? y : z);
}

/**
 * Finds the minimum number of coins with denominations 1, 3, 4 that changes
 * using the naive approach
 * @param n integer.
 * @returns minimum number of coins.
 */
int get_change_naive(int n) {
    if (n <= 1) {
        return 1;
    } else if (n == 3) {
        return 1;
    } else if (n == 4) {
        return 1;
    }
    return min(get_change_naive(n - 1), get_change_naive(n - 3),
               get_change_naive(n - 4)) +
           1;
}

/**
 * Finds the minimum number of coins with denominations 1, 3, 4 that changes
 * using dynamic programming.
 * @param n integer.
 * @returns minimum number of coins.
 */
int get_change(int m) {
    vector<int> record(m);
    for (int i{}; i < 4; i++) {
        record[i] = get_change_naive(i + 1);
    }
    for (int i{4}; i < m; i++) {
        record[i] = min(record[i - 1], record[i - 3], record[i - 4]) + 1;
    }
    return record[m - 1];
}

int main() {
    int m;
    std::cin >> m;
    std::cout << get_change(m) << '\n';
}
