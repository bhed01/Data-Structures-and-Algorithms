/**
 * The goal in this code problem is to check whether an input sequence
   contains a majority element.
 * @file majority_element.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
*/

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using std::vector;

/**
 * Returns the majority element if present.
 * @param a vector of integeres.
 * @returns majority element if present.
 * @returns -1 if not present.
 */
int get_majority_element(vector<int> &a) {
    std::unordered_map<int, int> record;
    for (auto element : a) {
        if (record.count(element) > 0) {
            record[element]++;
        } else {
            record[element] = 1;
        }
    }
    for (auto element : record) {
        if (element.second > a.size() / 2) return element.first;
    }
    return -1;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    std::cout << (get_majority_element(a) != -1) << '\n';
}
