/**
 * Program to implement an algorithm for the construction of suffix array of a
 * string.
 * @file suffix_array.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 **/
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

/**
 * Function to construct suffix array of a string.
 * @param text string
 * @return vector denoting the suffix array of string.
 **/
vector<int> BuildSuffixArray(const string& text) {
    vector<int> result(text.size());
    vector<string> suffixes(text.size());
    for (int i{}; i < text.size(); i++) {
        suffixes[i] = text.substr(i);
    }
    sort(suffixes.begin(), suffixes.end());
    for (int i{}; i < suffixes.size(); i++) {
        result[i] = text.size() - suffixes[i].size();
    }

    return result;
}

int main() {
    string text;
    cin >> text;
    vector<int> suffix_array = BuildSuffixArray(text);
    for (int i = 0; i < suffix_array.size(); ++i) {
        cout << suffix_array[i] << ' ';
    }
    cout << endl;
    return 0;
}
