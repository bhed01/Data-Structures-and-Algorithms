/**
 * Program to implement string matching algorithm using suffix array of string.
 * @file suffix_array_matching.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 **/
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

using std::cin;
using std::map;
using std::string;
using std::unordered_map;
using std::vector;

class BWT {
    string text;
    int size;
    vector<int> Order;
    vector<int> Class;
    unordered_map<char, int> starts;
    unordered_map<char, vector<int> > occ_count_before;

    void SortCharacters() {
        map<char, int> count;
        for (int i{}; i < size; i++) {
            if (count.find(text[i]) == count.end())
                count[text[i]] = 1;
            else
                count[text[i]]++;
        }
        int pre{};
        for (auto& el : count) {
            el.second += pre;
            pre = el.second;
        }
        for (int i{size - 1}; i >= 0; i--) {
            count[text[i]] -= 1;
            Order[count[text[i]]] = i;
        }
    }

    void ComputeClasses() {
        for (int i{1}; i < size; i++) {
            if (text[Order[i]] != text[Order[i - 1]]) {
                Class[Order[i]] = Class[Order[i - 1]] + 1;
            } else {
                Class[Order[i]] = Class[Order[i - 1]];
            }
        }
    }

    vector<int> SortDouble(int l) const {
        vector<int> newOrder(size);
        vector<int> count(size);
        for (int i{}; i < size; i++) {
            count[Class[i]]++;
        }
        for (int i{1}; i < size; i++) {
            count[i] += count[i - 1];
        }
        for (int i{size - 1}; i >= 0; i--) {
            int j{(Order[i] - l + size) % size};
            count[Class[j]]--;
            newOrder[count[Class[j]]] = j;
        }
        return newOrder;
    }

    vector<int> UpdateClass(int l) const {
        vector<int> newClass(size);

        for (int i{1}; i < size; i++) {
            int cur{Order[i]}, prev{Order[i - 1]};
            int mid{(cur + l + size) % size}, midPrev{(prev + l + size) % size};
            if ((Class[cur] != Class[prev]) || (Class[mid] != Class[midPrev]))
                newClass[cur] = newClass[prev] + 1;
            else
                newClass[cur] = newClass[prev];
        }

        return newClass;
    }

    void BuildSuffixArray() {
        SortCharacters();
        ComputeClasses();
        int l{1};
        while (l < size) {
            Order = SortDouble(l);
            Class = UpdateClass(l);
            l *= 2;
        }
    }

    void PreprocessBWT() {
        map<char, int> char_count{
            {'$', 0}, {'A', 0}, {'C', 0}, {'G', 0}, {'T', 0}};
        char Ch[]{'$', 'A', 'C', 'G', 'T'};
        for (auto C : Ch) {
            occ_count_before[C].push_back(0);
        }
        for (int i{}; i < size; i++) {
            char_count[text[(Order[i] - 1 + size) % size]]++;
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

   public:
    BWT(string text) : text(text), size((int)text.size()) {
        Order.resize(size);
        Class.resize(size);
        starts = {{'$', 0}, {'A', 0}, {'C', 0}, {'G', 0}, {'T', 0}};
        BuildSuffixArray();
        PreprocessBWT();
    }
    vector<int> FindOccurrences(const string& pattern) {
        vector<int> result;
        int top{}, bottom = size - 1;
        int pat_ind = pattern.size() - 1;
        while (top <= bottom) {
            if (pat_ind >= 0) {
                if (occ_count_before.at(pattern[pat_ind])[bottom + 1] >
                    occ_count_before.at(pattern[pat_ind])[top]) {
                    top = starts.at(pattern[pat_ind]) +
                          occ_count_before.at(pattern[pat_ind])[top];
                    bottom = starts.at(pattern[pat_ind]) +
                             occ_count_before.at(pattern[pat_ind])[bottom + 1] -
                             1;
                } else {
                    break;
                }
                pat_ind--;
            } else {
                for (int i{top}; i < bottom + 1; i++) {
                    result.push_back(Order[i]);
                }
                break;
            }
        }
        return result;
    }
};

int main() {
    char buffer[100001];
    scanf("%s", buffer);
    string text = buffer;
    text += '$';
    BWT bwt(text);

    int pattern_count;
    scanf("%d", &pattern_count);
    vector<bool> occurs(text.length(), false);
    for (int pattern_index = 0; pattern_index < pattern_count;
         ++pattern_index) {
        scanf("%s", buffer);
        string pattern          = buffer;
        vector<int> occurrences = bwt.FindOccurrences(pattern);
        for (int j = 0; j < occurrences.size(); ++j) {
            occurs[occurrences[j]] = true;
        }
    }
    for (int i = 0; i < occurs.size(); ++i) {
        if (occurs[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
    return 0;
}