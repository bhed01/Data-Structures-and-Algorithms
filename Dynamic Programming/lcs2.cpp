/**
 * The goal of this problem is to implement the algorithm for computing the
 * length of a longest common subsequence of two sequences.
 * @file lcs2.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 */
#include <iostream>
#include <vector>

using std::vector;
/**
 * Finds the the length of a longest common subsequence of two sequences.
 * @param a vector denoting sequence 1.
 * @param b vecotr denoting sequence 2.
 * @returns length of longest common subsequence.
 */
int lcs2(vector<int> &a, vector<int> &b) {
    int an{(int)a.size()}, bn{(int)b.size()};
    int record[an + 1][bn + 2];
    for (int i{}; i <= an; i++) record[i][0] = 0;
    for (int i{}; i <= bn; i++) record[0][i] = 0;
    for (int i{1}; i <= an; i++) {
        for (int j{1}; j <= bn; j++) {
            if (a[i - 1] == b[j - 1])
                record[i][j] =
                    std::max(std::max(record[i - 1][j], record[i][j - 1]),
                             record[i - 1][j - 1] + 1);
            else
                record[i][j] =
                    std::max(std::max(record[i - 1][j], record[i][j - 1]),
                             record[i - 1][j - 1]);
        }
    }
    return record[an][bn];
}

int main() {
    size_t n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    size_t m;
    std::cin >> m;
    vector<int> b(m);
    for (size_t i = 0; i < m; i++) {
        std::cin >> b[i];
    }

    std::cout << lcs2(a, b) << std::endl;
}
