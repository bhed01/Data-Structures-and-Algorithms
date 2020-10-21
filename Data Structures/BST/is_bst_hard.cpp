/**
 * The goal of this program is to implement an algorithm to check whether given
 * tree is BST or not.
 **/
#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

/**
 * Sturcture for the node of the tree.
 **/
struct Node {
    int key;    /// stores the value at node.
    int left;   /// index of left child.
    int right;  /// index of right child.

    // constructors
    Node() : key(0), left(-1), right(-1) {}
    Node(int key_, int left_, int right_)
        : key(key_), left(left_), right(right_) {}
};

/**
 * Function for in-order traversal of tree to check whether it is BST.
 * @param i index of current node.
 * @param tree tree stored in the form of a vector.
 * @param result vector to be updated with the traversal order.
 **/
bool in_order_util(int i, const vector<Node>& tree, vector<int>& result) {
    if (tree[i].left != -1) {
        if (tree[i].key <= tree[tree[i].left].key) return false;
        if (!in_order_util(tree[i].left, tree, result)) return false;
    }
    result.push_back(tree[i].key);
    if (tree[i].right != -1) {
        if (tree[i].key > tree[tree[i].right].key) return false;
        if (!in_order_util(tree[i].right, tree, result)) return false;
    }
    return true;
}

bool in_order(const vector<Node>& tree, vector<int>& result) {
    if (in_order_util(0, tree, result))
        return true;
    else
        return false;
}

/**
 * Function to check whether tree is BST or not.
 * @param tree stored in form of a vector.
 * @return ture if tree is BST else false.
 **/
bool IsBinarySearchTree(const vector<Node>& tree) {
    if (tree.size() == 0) return true;
    vector<int> result;
    if (!in_order(tree, result)) return false;
    for (int i{1}; i < result.size(); i++) {
        if (result[i - 1] > result[i]) return false;
    }
    return true;
}

int main() {
    int nodes;
    cin >> nodes;
    vector<Node> tree;
    for (int i = 0; i < nodes; ++i) {
        int key, left, right;
        cin >> key >> left >> right;
        tree.push_back(Node(key, left, right));
    }
    if (IsBinarySearchTree(tree)) {
        cout << "CORRECT" << endl;
    } else {
        cout << "INCORRECT" << endl;
    }
    return 0;
}
