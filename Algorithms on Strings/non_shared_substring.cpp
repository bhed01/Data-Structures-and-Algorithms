/**
 * Program to implement an algorithm for finding the shortest nod non shared
 * substring of two strings.
 * @file non_shared_substring.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 **/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * Sturcture to store a node of tree.
 **/
struct node {
    int start, size;
    vector<node*> child;
    node() : start(-1), size(0) {}
    node(int start, int size) : start(start), size(size) {}
};

class SuffixTree {
    string text;
    node* root;
    int plen;
    int qlen;

    /**
     * Function to build the suffix tree
     **/
    void build() {
        for (int k{1}; k < (int)text.size(); k++) {
            int i{k};
            node* cur = root;
            while (i < (int)text.size()) {
                bool found{false};
                for (int j{}; j < cur->child.size(); j++) {
                    if (text[i] == text[cur->child[j]->start]) {
                        int offset{};
                        while ((offset < cur->child[j]->size) &&
                               (text[i + offset] ==
                                text[cur->child[j]->start + offset]))
                            offset++;
                        if (cur->child[j]->size > offset) {
                            node* n = new node(cur->child[j]->start, offset);
                            cur->child[j]->start += offset;
                            cur->child[j]->size -= offset;
                            n->child.push_back(cur->child[j]);
                            cur->child[j] = n;
                            cur           = n;
                        } else {
                            cur = cur->child[j];
                        }
                        i += offset;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    node* n = new node(i, text.size() - i);
                    cur->child.push_back(n);
                    break;
                }
            }
        }
    }

    /**
     * Utility Function for solving the problem.
     * @param cur pointer of a node.
     * @param allP
     * @return non matching string.
     **/
    string solve_util(node* cur, bool& allP) {
        if (cur->start > plen) return "";
        if (cur->start == plen) return "#";
        if (text[cur->start + cur->size - 1] == '$')
            return text.substr(cur->start, 1);
        string result = text.substr(cur->start, cur->size);
        int minlen{plen};
        bool modified{false};
        string newStr;
        for (int i{}; i < cur->child.size(); i++) {
            string temp = solve_util(cur->child[i], allP);
            if (temp == "") {
                allP = false;
            }
            if ((temp != "") && (temp[0] != '#') &&
                ((int)temp.size() < minlen)) {
                minlen   = temp.size();
                newStr   = temp;
                modified = true;
            }
        }
        if (allP) return text.substr(cur->start, 1);
        if (!modified) return "#";
        result.append(newStr);
        return result;
    }

   public:
    /**
     * Constructor for initializing the variable appropriately.
     **/
    SuffixTree(string p, string q) : plen(p.size()), qlen(q.size()) {
        p.push_back('#');
        p.append(q);
        p.push_back('$');
        text       = p;
        root       = new node();
        node* temp = new node(0, text.size());
        root->child.push_back(temp);
        build();
    }

    /**
     * Function for solving the problem.
     * @return shortest non-matching substring.
     **/
    string solve() {
        int minlen{plen + 1};
        string result;
        for (int i{}; i < root->child.size(); i++) {
            bool allP{true};
            string temp = solve_util(root->child[i], allP);
            if ((temp != "") && (temp[0] != '#') &&
                ((int)temp.size() < minlen)) {
                minlen = temp.size();
                result = temp;
            }
        }

        return result;
    }
};

int main(void) {
    string p;
    cin >> p;
    string q;
    cin >> q;
    SuffixTree solver(p, q);
    cout << solver.solve() << endl;
    return 0;
}
