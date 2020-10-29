/**
 * Program to implement an algorithm for retrieving original string for
 * Burrows-Wheeler transform of a string.
 * @file bwtinverse.cpp
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
using std::pair;
using std::string;
using std::vector;

/**
 * Function to convert character to index.
 * @param ch character
 * @return index of the character.
 **/
int getInd(char ch) {
    switch (ch) {
        case 'A':
            return 1;
        case 'C':
            return 2;
        case 'G':
            return 3;
        case 'T':
            return 4;
        default:
            return 0;
    }
}

/**
 * Function to retrieve original string from BWT.
 * @param bwt Burrows-Wheeler transform of a string.
 * @return original string.
 **/
string InverseBWT(const string& bwt) {
    string text = "$";

    vector<int> bwtind(bwt.size());
    vector<pair<int, int>> dict(5);
    for (int i{}; i < bwt.size(); i++) {
        int ind = getInd(bwt[i]);
        dict[ind].first += 1;
        bwtind[i] = dict[ind].first;
    }
    for (int i{1}; i < dict.size(); i++) {
        dict[i].second = dict[i - 1].first + dict[i - 1].second;
    }
    int cur{};
    while (bwt[cur] != '$') {
        text.push_back(bwt[cur]);
        cur = dict[getInd(bwt[cur])].second + bwtind[cur] - 1;
    }
    reverse(text.begin(), text.end());
    return text;
}

int main() {
    string bwt;
    cin >> bwt;
    cout << InverseBWT(bwt) << endl;
    return 0;
}
