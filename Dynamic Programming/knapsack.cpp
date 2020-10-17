/**
 * Given n gold bars, the goal of this problem is to implement the algorithm for
 * finding the maximum weight of gold that fits into a bag of capacity W .
 * @file knapsack.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 */
#include <iostream>
#include <vector>

using std::vector;
/**
 * Finds the maximum weight of gold that fits into bag of capacity W.
 * @param W integer capacity of bag.
 * @param w vector integers denoting weights of different gold bar.
 * @returns interger value denoting maximum weight.
 */
int optimal_weight(int W, const vector<int> &w) {
    int n{(int)w.size()};
    int temp{2};
    int record[temp][W + 1]{};
    int r{1};
    for (int i{1}; i <= n; i++) {
        for (int j{1}; j <= W; j++) {
            if (j - w[i - 1] >= 0)
                record[r][j] = std::max(record[!r][j],
                                        record[!r][j - w[i - 1]] + w[i - 1]);
            else
                record[r][j] = record[!r][j];
        }
        r = !r;
    }
    return record[!r][W];
}

int main() {
    int n, W;
    std::cin >> W >> n;
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        std::cin >> w[i];
    }
    std::cout << optimal_weight(W, w) << '\n';
}
