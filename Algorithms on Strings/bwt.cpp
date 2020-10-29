/**
 * Program to implement an algorithm for construction of Burrows-Wheeler
 * tranform of a string.
 * @file bwt.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 **/
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

/**
 * Function to construct Burrows-Wheeler transform from string.
 * @param text string to be converted.
 * @return transformed string.
 **/
string BWT(const string& text) {
    string result = "";
    vector<string> suffixes(text.size());
    for (int i{}; i < text.size(); i++) {
        suffixes[i] = text.substr(i);
    }
    sort(suffixes.begin(), suffixes.end());
    for (auto& suffix : suffixes) {
        if (suffix.size() == text.size())
            result.push_back('$');
        else
            result.push_back(text[text.size() - suffix.size() - 1]);
    }
    return result;
}

int main() {
    string text;
    cin >> text;
    cout << BWT(text) << endl;
    return 0;
}