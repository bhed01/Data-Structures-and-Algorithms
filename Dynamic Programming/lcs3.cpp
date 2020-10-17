/**
 * The goal of this problem is to implement the algorithm for computing the
 * length of a longest common subsequence of three sequences.
 * @file lcs3.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 */
#include <algorithm>
#include <iostream>
#include <vector>

using std::max;
using std::max_element;
using std::vector;
/**
 * Finds the the length of a longest common subsequence of three sequences.
 * @param a vector denoting sequence 1.
 * @param b vecotr denoting sequence 2.
 * @param c vecotr denoting sequence 3.
 * @returns length of longest common subsequence.
 */
int lcs3(vector<int> &a, vector<int> &b, vector<int> &c) {
    size_t an{a.size()}, bn{b.size()}, cn{c.size()};
    int record[an + 1][bn + 1][cn + 1]{};
    for (int i{1}; i <= an; i++) {
        for (int j{1}; j <= bn; j++) {
            for (int k{1}; k <= cn; k++) {
                int temp[]{record[i - 1][j][k], record[i - 1][j - 1][k],
                           record[i][j - 1][k], record[i][j - 1][k - 1],
                           record[i][j][k - 1], record[i - 1][j][k - 1]};
                int max_temp = *max_element(temp, temp + 5);
                if ((a[i - 1] == b[j - 1]) && (a[i - 1] == c[k - 1]))
                    record[i][j][k] =
                        max(max_temp, record[i - 1][j - 1][k - 1] + 1);
                else
                    record[i][j][k] =
                        max(max_temp, record[i - 1][j - 1][k - 1]);
            }
        }
    }
    return record[an][bn][cn];
}

int main() {
    size_t an;
    std::cin >> an;
    vector<int> a(an);
    for (size_t i = 0; i < an; i++) {
        std::cin >> a[i];
    }
    size_t bn;
    std::cin >> bn;
    vector<int> b(bn);
    for (size_t i = 0; i < bn; i++) {
        std::cin >> b[i];
    }
    size_t cn;
    std::cin >> cn;
    vector<int> c(cn);
    for (size_t i = 0; i < cn; i++) {
        std::cin >> c[i];
    }
    std::cout << lcs3(a, b, c) << std::endl;
}
