/**
 * The goal of this problem is to implement the algorithm for finding the
 * maximum integer in every subarray of size 'm'.
 * @file max_sliding_window.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 */
#include <deque>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

/**
 * Prints the maximum of all the subarrya of size 'w'.
 * @param A the array contianing integers
 * @param w window size
 **/
void max_sliding_window(vector<int> const& A, int w) {
    std::deque<int> max_ind;
    for (size_t i{}; i < w; i++) {
        if (max_ind.empty()) {
            max_ind.push_back(i);
        } else {
            while (!max_ind.empty() && A[max_ind.back()] < A[i]) {
                max_ind.pop_back();
            }
            max_ind.push_back(i);
        }
    }
    cout << A[max_ind.front()] << " ";
    for (size_t i = w; i < A.size(); i++) {
        if (max_ind.front() <= i - w) {
            max_ind.pop_front();
        }
        if (max_ind.empty()) {
            max_ind.push_back(i);
        } else {
            while (!max_ind.empty() && A[max_ind.back()] < A[i]) {
                max_ind.pop_back();
            }
            max_ind.push_back(i);
        }
        cout << A[max_ind.front()] << " ";
    }
}

int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i) cin >> A.at(i);

    int w = 0;
    cin >> w;

    max_sliding_window(A, w);

    return 0;
}
