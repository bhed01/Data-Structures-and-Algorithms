/**
 * The goal of this problem is to implement the algorithm for finding the
 * maximum value of an arithmetic expression by specifying the order of applying
 * its arithmetic operations using additional parentheses.
 * @file placing_parantheses.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 */
#include <cassert>
#include <climits>
#include <iostream>
#include <string>
#include <vector>

using std::max;
using std::min;
using std::string;
using std::vector;
/**
 * Finds the value of operation op on a and b.
 * @param a long long int.
 * @param b long long int.
 * @param op char denoting operation to be performed.
 * @returns value of operation on a and b.
 */
long long eval(long long a, long long b, char op) {
    if (op == '*') {
        return a * b;
    } else if (op == '+') {
        return a + b;
    } else if (op == '-') {
        return a - b;
    } else {
        assert(0);
    }
}

/**
 * Finds the maximum value that can be obtained by changing the order of
 * operations.
 * @param exp string denoting expression.
 * @returns maximum value of expression.
 */
long long get_maximum_value(const string &exp) {
    long long n{(long long)exp.length() / 2 + 1};
    long long min_record[n][n]{0};
    long long max_record[n][n]{0};
    for (size_t i{}; i < n; i++) {
        min_record[i][i] = exp[2 * i] - 48;
        max_record[i][i] = min_record[i][i];
    }
    for (size_t g{1}; g < n; g++) {
        for (size_t i{0}; i < n - g; i++) {
            long long min_val{LLONG_MAX}, max_val{LLONG_MIN};
            string sub_exp{exp.substr(i * 2, 2 * g + 1)};
            for (size_t j{1}; j < 2 * g + 1; j += 2) {
                if (sub_exp[j] == '*') {
                    if (i + j / 2 + 1 <= i + g && i + j / 2 <= i + g) {
                        min_val = min(min_val,
                                      min(eval(min_record[i][i + j / 2],
                                               max_record[i + j / 2 + 1][i + g],
                                               sub_exp[j]),
                                          eval(max_record[i][i + j / 2],
                                               min_record[i + j / 2 + 1][i + g],
                                               sub_exp[j])));
                        max_val = max(max_val,
                                      max(eval(min_record[i][i + j / 2],
                                               min_record[i + j / 2 + 1][i + g],
                                               sub_exp[j]),
                                          eval(max_record[i][i + j / 2],
                                               max_record[i + j / 2 + 1][i + g],
                                               sub_exp[j])));
                    }
                } else if (sub_exp[j] == '+') {
                    if (i + j / 2 + 1 <= i + g && i + j / 2 <= i + g) {
                        min_val =
                            min(min_val, eval(min_record[i][i + j / 2],
                                              min_record[i + j / 2 + 1][i + g],
                                              sub_exp[j]));
                        max_val =
                            max(max_val, eval(max_record[i][i + j / 2],
                                              max_record[i + j / 2 + 1][i + g],
                                              sub_exp[j]));
                    }
                } else {
                    if (i + j / 2 + 1 <= i + g && i + j / 2 <= i + g) {
                        min_val =
                            min(min_val, eval(min_record[i][i + j / 2],
                                              max_record[i + j / 2 + 1][i + g],
                                              sub_exp[j]));
                        max_val =
                            max(max_val, eval(max_record[i][i + j / 2],
                                              min_record[i + j / 2 + 1][i + g],
                                              sub_exp[j]));
                    }
                }
            }
            min_record[i][i + g] = min_val;
            max_record[i][i + g] = max_val;
        }
    }
    return max_record[0][n - 1];
}

int main() {
    string s;
    std::cin >> s;
    std::cout << get_maximum_value(s) << '\n';
}
