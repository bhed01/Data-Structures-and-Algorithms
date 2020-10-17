/**
 * Goal of this program is to implement the algorithm to find the minimum number
 * of operations needed to obtain a number 'n' starting form 1.
 * @file primitive_calculator.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 */
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using std::pair;
using std::vector;
/**
 * Finds the minimum number of operations needed to obtain number 'n' starting
 * from 1.
 * @param n int.
 * @returns int denoting minimum number of operations.
 */
vector<int> optimal_sequence(int n) {
    std::vector<pair<int, int>> record(n);
    record[0] = std::make_pair(0, 1);
    record[1] = std::make_pair(1, 1);
    record[2] = std::make_pair(1, 1);
    for (int i{3}; i < n; i++) {
        if ((i + 1) % 2 == 0) {
            if ((i + 1) % 3 == 0) {
                if (record[i - 1].first < record[(i + 1) / 2 - 1].first) {
                    if (record[i - 1].first < record[(i + 1) / 3 - 1].first) {
                        record[i] =
                            std::make_pair(record[i - 1].first + 1, i - 1);
                    } else {
                        record[i] = std::make_pair(
                            record[(i + 1) / 3 - 1].first + 1, (i + 1) / 3 - 1);
                    }
                } else {
                    if (record[(i + 1) / 2 - 1].first <
                        record[(i + 1) / 3 - 1].first) {
                        record[i] = std::make_pair(
                            record[(i + 1) / 2 - 1].first + 1, (i + 1) / 2 - 1);
                    } else {
                        record[i] = std::make_pair(
                            record[(i + 1) / 3 - 1].first + 1, (i + 1) / 3 - 1);
                    }
                }
            } else {
                if (record[i - 1].first < record[(i + 1) / 2 - 1].first) {
                    record[i] = std::make_pair(record[i - 1].first + 1, i - 1);
                } else {
                    record[i] = std::make_pair(
                        record[(i + 1) / 2 - 1].first + 1, (i + 1) / 2 - 1);
                }
            }
        } else {
            if ((i + 1) % 3 == 0) {
                if (record[i - 1].first < record[(i + 1) / 3 - 1].first) {
                    record[i] = std::make_pair(record[i - 1].first + 1, i - 1);
                } else {
                    record[i] = std::make_pair(
                        record[(i + 1) / 3 - 1].first + 1, (i + 1) / 3 - 1);
                }
            } else
                record[i] = std::make_pair(record[i - 1].first + 1, i - 1);
        }
    }
    int min_op{record[n - 1].first};
    std::vector<int> sequence(min_op + 1);

    sequence[min_op] = n;

    for (int i{min_op - 1}; i > 0; i--) {
        sequence[i] = record[sequence[i + 1] - 1].second + 1;
    }
    sequence[0] = 1;
    return sequence;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> sequence = optimal_sequence(n);
    std::cout << sequence.size() - 1 << std::endl;
    for (size_t i = 0; i < sequence.size(); ++i) {
        std::cout << sequence[i] << " ";
    }
}
