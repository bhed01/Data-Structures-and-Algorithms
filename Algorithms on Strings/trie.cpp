/**
 * The goal of this program is to implement an algorithm for the construction of
 * trie from a collection of patterns.
 * @file trie.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 **/
#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

typedef map<char, int> edges;
typedef vector<edges> trie;

/**
 * Function to construct the trie from the array of patterns.
 * @param patterns array of different pattern strings.
 * @return trie as vector of map.
 **/
trie build_trie(vector<string> &patterns) {
    trie t;
    int vcount{1};
    for (auto &pattern : patterns) {
        int cur{};
        for (auto &ch : pattern) {
            if (cur >= t.size()) {
                while (t.size() < cur) t.push_back({{'$', -1}});
                t.push_back({{ch, vcount}});
                cur = vcount++;
            } else {
                if (t[cur].find(ch) == t[cur].end()) {
                    t[cur][ch] = vcount;
                    cur        = vcount++;
                } else {
                    cur = t[cur][ch];
                }
            }
        }
    }
    return t;
}

int main() {
    size_t n;
    std::cin >> n;
    vector<string> patterns(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> patterns[i];
    }

    trie t = build_trie(patterns);
    for (size_t i = 0; i < t.size(); ++i) {
        for (const auto &j : t[i]) {
            if (j.second != -1)
                std::cout << i << "->" << j.second << ":" << j.first << "\n";
        }
    }

    return 0;
}