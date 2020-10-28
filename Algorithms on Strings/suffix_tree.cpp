/**
 * Program to implement the algorithm for the construction of suffix tree of a
 * string.
 * @file suffix_tree.cpp
 * @author Bhed Kumar Kushwah
 * @version 1.0
 **/
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::vector;

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
    vector<string> result;

    /**
     * Function for DFS of a tree node.
     * @param n pointer to a node.
     **/
    void dfs(node* n) {
        result.push_back(text.substr(n->start, n->size));
        for (int i{}; i < n->child.size(); i++) {
            dfs(n->child[i]);
        }
    }

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

   public:
    /**
     * Constructor for initializing the variable appropriately.
     **/
    SuffixTree(string text) : text(text) {
        root       = new node();
        node* temp = new node(0, text.size());
        root->child.push_back(temp);
        build();
    }

    /**
     * Function to compute each edge of the tree.
     * @return vector of the strings denoting edges
     **/
    vector<string> edges() {
        for (int i{}; i < root->child.size(); i++) {
            dfs(root->child[i]);
        }
        return result;
    }
};

int main() {
    string text;
    cin >> text;
    SuffixTree tree(text);
    vector<string> edges = tree.edges();
    for (int i = 0; i < edges.size(); ++i) {
        cout << edges[i] << endl;
    }
    return 0;
}
