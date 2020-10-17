/**
 * The goal of this problem is to implement the algorithm for paritioning the
 * array into 3 parts with equal sum.
 * @file partition3.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 */
#include <iostream>
#include <numeric>
#include <vector>

using std::vector;
/**
 * Finds if it is possible to split the array into 3 subarrays of equal sum.
 * @param A vector of integers.
 * @returns 1 if possible.
 * @returns 0 if not possible.
 */
int partition3(vector<int> &A) {
    int total{std::accumulate(A.begin(), A.end(), 0)};
    if (total % 3 == 0) {
        for (int _{1}; _ < 3; _++) {
            int w{(total * _) / 3};
            int n{(int)A.size()};
            int temp{2};
            int record[temp][w + 1]{};
            int r{1};
            for (int i{1}; i <= n; i++) {
                for (int j{1}; j <= w; j++) {
                    if (j - A[i - 1] >= 0)
                        record[r][j] = std::max(
                            record[!r][j - A[i - 1]] + A[i - 1], record[!r][j]);
                    else
                        record[r][j] = record[!r][j];
                }
                r = !r;
            }
            if (record[!r][w] != w) {
                return 0;
            }
        }
        return 1;
    } else
        return 0;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> A(n);
    for (size_t i = 0; i < A.size(); ++i) {
        std::cin >> A[i];
    }
    std::cout << partition3(A) << '\n';
}
