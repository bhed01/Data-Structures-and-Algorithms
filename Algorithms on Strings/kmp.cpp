/**
 * Program to implement the Knuth Morris Pratt's algorithm.
 * @file kmp.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 **/
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;

/**
 * Function to find the all occurrencs of a pattern in a string using the Knuth
 * Morris Pratt's Algorithm.
 * @param pattern pattern to be searched
 * @param text string in which all the occurrence has to be found.
 * @return vector of all matching indices.
 **/
vector<int> find_pattern(const string& pattern, const string& text) {
    vector<int> result;
    string temp = pattern + "$" + text;
    vector<int> border(temp.size());
    int j{};
    for (int i{1}; i < (int)temp.size(); i++) {
        while ((j > 0) && (temp[i] != temp[j])) j = border[j - 1];

        if (temp[j] == temp[i]) border[i] = j + 1;
        j = border[i];
    }
    for (int i{(int)pattern.size()}; i < (int)temp.size(); i++) {
        if (border[i] == pattern.size())
            result.push_back(i - 2 * pattern.size());
    }
    return result;
}

int main() {
    string pattern, text;
    cin >> pattern;
    cin >> text;
    vector<int> result = find_pattern(pattern, text);
    for (int i = 0; i < result.size(); ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");
    return 0;
}
