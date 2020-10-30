/**
 * Program to implement an algorithm for contructing suffix array of a string.
 * @file auffix_array_long.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 **/
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::map;
using std::pair;
using std::string;
using std::vector;

/**
 * Function to sort all the characters of a string using count sort.
 * @param text string of characters to be sorted.
 * @param order vector in which the order of charater is to be stored.
 **/
void SortCharacters(const string& text, vector<int>& order) {
    map<char, int> count;
    for (int i{}; i < (int)text.size(); i++) {
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
    for (int i{(int)text.size() - 1}; i >= 0; i--) {
        count[text[i]] -= 1;
        order[count[text[i]]] = i;
    }
}

/**
 * Funtion to compute the class.
 * @param text
 * @param order Order of the sorted characters
 * @param Class vector denoting the class of each string.
 **/
void ComputeClasses(const string& text, const vector<int>& order,
                    vector<int>& Class) {
    for (int i{1}; i < (int)text.size(); i++) {
        if (text[order[i]] != text[order[i - 1]]) {
            Class[order[i]] = Class[order[i - 1]] + 1;
        } else {
            Class[order[i]] = Class[order[i - 1]];
        }
    }
}

vector<int> SortDouble(const string& text, int l, const vector<int>& order,
                       const vector<int>& Class) {
    int n = text.size();
    vector<int> newOrder(n);
    vector<int> count(n);
    for (int i{}; i < n; i++) {
        count[Class[i]]++;
    }
    for (int i{1}; i < n; i++) {
        count[i] += count[i - 1];
    }
    for (int i{n - 1}; i >= 0; i--) {
        int j{(order[i] - l + n) % n};
        count[Class[j]]--;
        newOrder[count[Class[j]]] = j;
    }
    return newOrder;
}

vector<int> UpdateClass(const vector<int>& order, const vector<int>& Class,
                        int l) {
    int n = order.size();
    vector<int> newClass(n);

    for (int i{1}; i < n; i++) {
        int cur{order[i]}, prev{order[i - 1]};
        int mid{(cur + l + n) % n}, midPrev{(prev + l + n) % n};
        if ((Class[cur] != Class[prev]) || (Class[mid] != Class[midPrev]))
            newClass[cur] = newClass[prev] + 1;
        else
            newClass[cur] = newClass[prev];
    }

    return newClass;
}

vector<int> BuildSuffixArray(const string& text) {
    vector<int> order(text.size());
    vector<int> Class(text.size());
    SortCharacters(text, order);
    ComputeClasses(text, order, Class);
    int l{1};
    while (l < text.size()) {
        order = SortDouble(text, l, order, Class);
        Class = UpdateClass(order, Class, l);
        l *= 2;
    }
    return order;
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
