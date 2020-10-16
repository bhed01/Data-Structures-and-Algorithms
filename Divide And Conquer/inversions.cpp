/**
 * The goal in this problem is to count the number of inversions of a given
   sequence.
 * @file inversions.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 */

#include <iostream>
#include <vector>

using std::vector;

/**
 * Returns the total number of inversions required for array to be sorted.
 * @param a vector of integeres.
 * @param b vector of integeres.
 * @param left starting index of vector.
 * @param right ending index of vector.
 * @returns number of inversions.
 */
long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left,
                                   size_t right) {
    long long number_of_inversions{};
    if (right <= left + 1) {
        b[left] = a[left];
        return number_of_inversions;
    }
    size_t ave = left + (right - left) / 2;
    number_of_inversions += get_number_of_inversions(a, b, left, ave);
    number_of_inversions += get_number_of_inversions(a, b, ave, right);
    size_t i{left}, j{ave}, k{left};
    vector<int> temp = b;
    while (i < ave && j < right) {
        if (temp[i] > temp[j]) {
            number_of_inversions += ave - i;
            b[k++] = temp[j++];
        } else {
            b[k++] = temp[i++];
        }
    }
    while (i < ave) {
        b[k++] = temp[i++];
    }
    while (j < right) {
        b[k++] = temp[j++];
    }

    return number_of_inversions;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    vector<int> b(a.size());
    std::cout << get_number_of_inversions(a, b, 0, a.size()) << '\n';
}
