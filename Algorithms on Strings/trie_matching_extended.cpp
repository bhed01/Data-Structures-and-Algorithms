/**
 * Program to implement the trie maching algorithm.
 * @file trie_matching.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 **/

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

typedef map<char, int> edges;
typedef vector<edges> trie;

/**
 * Function to construct the trie from the array of patterns.
 * @param patterns array of different pattern strings.
 * @return trie as vector of map.
 **/
trie build_trie(const vector<string> &patterns) {
    trie t;
    int vcount{1};
    for (auto &pattern : patterns) {
        int cur{};
        for (auto &ch : pattern) {
            if (cur >= t.size()) {
                while (t.size() < cur) t.push_back({{'$', -2}});
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
        if (cur >= t.size()) {
            while (t.size() < cur) t.push_back({{'$', -2}});
            t.push_back({{'$', -1}});
        } else {
            t[cur]['$'] = -1;
        }
    }
    return t;
}

/**
 * Function to implement the trie matching.
 * @param text string against with matching has to be performed
 * @param patterns array of different pattern strings.
 * @return vector of indices where matching has occured.
 **/
vector<int> solve(const string &text, int n, const vector<string> &patterns) {
    vector<int> result;
    trie t = build_trie(patterns);

    for (int i{}; i < text.size(); i++) {
        int cur{};
        int offset{};
        bool match{true};
        while (cur < t.size()) {
            if (t[cur].find('$') != t[cur].end()) {
                break;
            } else if (t[cur].find(text[i + offset]) != t[cur].end()) {
                cur = t[cur][text[i + offset]];
                offset++;
            } else {
                match = false;
                break;
            }
        }
        if (match) {
            result.push_back(i);
        }
    }

    return result;
}

int main(void) {
    string t;
    cin >> t;

    int n;
    cin >> n;

    vector<string> patterns(n);
    for (int i = 0; i < n; i++) {
        cin >> patterns[i];
    }

    vector<int> ans;
    ans = solve(t, n, patterns);

    for (int i = 0; i < (int)ans.size(); i++) {
        cout << ans[i];
        if (i + 1 < (int)ans.size()) {
            cout << " ";
        } else {
            cout << endl;
        }
    }

    return 0;
}
