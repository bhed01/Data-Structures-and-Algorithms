/**
 * The goal of this problem is to implement the algorithm for computing the edit
 * distance between two strings.
 * @file edit_distance.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 */
#include <iostream>
#include <string>

using std::string;

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
 * Finds the edit distance between two strings.
 * @param str1 string.
 * @param str2 string.
 * @returns integer denoting edit distance between two strings.
 */
int edit_distance(const string &str1, const string &str2) {
    int n{(int)str1.length()}, m{(int)str2.length()};
    int record[n + 1][m + 1]{};
    record[0][0] = 0;
    for (int i{1}; i <= m; i++) {
        record[0][i] = record[0][i - 1] + 1;
    }
    for (int i{1}; i <= n; i++) {
        record[i][0] = record[i - 1][0] + 1;
    }
    for (int i{1}; i <= m; i++) {
        for (int j{1}; j <= n; j++) {
            if (str1[j - 1] == str2[i - 1])
                record[j][i] = min(record[j][i - 1] + 1, record[j - 1][i] + 1,
                                   record[j - 1][i - 1]);
            else
                record[j][i] = min(record[j][i - 1] + 1, record[j - 1][i] + 1,
                                   record[j - 1][i - 1] + 1);
        }
    }
    return record[n][m];
}

int main() {
    string str1;
    string str2;
    std::cin >> str1 >> str2;
    std::cout << edit_distance(str1, str2) << std::endl;
    return 0;
}
