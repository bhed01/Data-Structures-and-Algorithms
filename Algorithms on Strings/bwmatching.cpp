/**
 * Program to implement an algorithm for BWMatching.
 * @file bwmatching.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 **/
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using std::cin;
using std::istringstream;
using std::map;
using std::string;
using std::vector;

/**
 * Preprocess the Burrows-Wheeler Transform bwt of some text
 * and compute as a result:
 *    * starts - for each character C in bwt, starts[C] is the first position
 *        of this character in the sorted array of
 *        all characters of the text.
 *    * occ_count_before - for each character C in bwt and each position P in
 *    bwt,
 *        occ_count_before[C][P] is the number of occurrences of character C in
 *        bwt from position 0 to position P inclusive.
 **/
void PreprocessBWT(const string& bwt, map<char, int>& starts,
                   map<char, vector<int> >& occ_count_before) {
    map<char, int> char_count{{'$', 0}, {'A', 0}, {'C', 0}, {'G', 0}, {'T', 0}};
    char Ch[]{'$', 'A', 'C', 'G', 'T'};
    for (auto C : Ch) {
        occ_count_before[C].push_back(0);
    }
    for (int i{}; i < bwt.size(); i++) {
        char_count[bwt[i]]++;
        for (auto C : Ch) {
            occ_count_before[C].push_back(char_count[C]);
        }
    }
    int pre_count{};
    for (auto& el : char_count) {
        if (el.second != 0) starts[el.first] = pre_count;
        pre_count += el.second;
    }
}

/**
 * Compute the number of occurrences of string pattern in the text
 * given only Burrows-Wheeler Transform bwt of the text and additional
 * information we get from the preprocessing stage - starts and
 * occ_counts_before.
 **/
int CountOccurrences(const string& pattern, const string& bwt,
                     const map<char, int>& starts,
                     const map<char, vector<int> >& occ_count_before) {
    int top{}, bottom = bwt.size() - 1;
    int pat_ind = pattern.size() - 1;
    while (top <= bottom) {
        if (pat_ind >= 0) {
            if (occ_count_before.at(pattern[pat_ind])[bottom + 1] >
                occ_count_before.at(pattern[pat_ind])[top]) {
                top = starts.at(pattern[pat_ind]) +
                      occ_count_before.at(pattern[pat_ind])[top];
                bottom = starts.at(pattern[pat_ind]) +
                         occ_count_before.at(pattern[pat_ind])[bottom + 1] - 1;
            } else {
                return 0;
            }
            pat_ind--;
        } else {
            return bottom - top + 1;
        }
    }
    return 0;
}

int main() {
    string bwt;
    cin >> bwt;
    int pattern_count;
    cin >> pattern_count;
    // Start of each character in the sorted list of characters of bwt,
    // see the description in the comment about function PreprocessBWT
    map<char, int> starts{{'$', 0}, {'A', 0}, {'C', 0}, {'G', 0}, {'T', 0}};
    // Occurrence counts for each character and each position in bwt,
    // see the description in the comment about function PreprocessBWT
    map<char, vector<int> > occ_count_before;
    // Preprocess the BWT once to get starts and occ_count_before.
    // For each pattern, we will then use these precomputed values and
    // spend only O(|pattern|) to find all occurrences of the pattern
    // in the text instead of O(|pattern| + |text|).
    PreprocessBWT(bwt, starts, occ_count_before);
    for (int pi = 0; pi < pattern_count; ++pi) {
        string pattern;
        cin >> pattern;
        int occ_count =
            CountOccurrences(pattern, bwt, starts, occ_count_before);
        printf("%d ", occ_count);
    }
    printf("\n");
    return 0;
}
