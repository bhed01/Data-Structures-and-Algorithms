/**
 * The goal of this program is to implement algorithms of BST traversal.
 **/
#include <algorithm>
#include <iostream>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::cin;
using std::cout;
using std::ios_base;
using std::vector;

class TreeOrders {
    int n;
    vector<int> key;
    vector<int> left;
    vector<int> right;

    /**
     * function for in-order traversal of BST.
     * @param i index of current node.
     * @param result vector to be updated with the traversal order.
     **/
    void in_order_util(int i, vector<int> &result) {
        if (left[i] != -1) in_order_util(left[i], result);
        result.push_back(key[i]);
        if (right[i] != -1) in_order_util(right[i], result);
    }

    /**
     * function for pre-order traversal of BST.
     * @param i index of current node.
     * @param result vector to be updated with the traversal order.
     **/
    void pre_order_util(int i, vector<int> &result) {
        result.push_back(key[i]);
        if (left[i] != -1) pre_order_util(left[i], result);
        if (right[i] != -1) pre_order_util(right[i], result);
    }

    /**
     * function for post-order traversal of BST.
     * @param i index of current node.
     * @param result vector to be updated with the traversal order.
     **/
    void post_order_util(int i, vector<int> &result) {
        if (left[i] != -1) post_order_util(left[i], result);
        if (right[i] != -1) post_order_util(right[i], result);
        result.push_back(key[i]);
    }

   public:
    /**
     * Function to read input from console.
     **/
    void read() {
        cin >> n;
        key.resize(n);
        left.resize(n);
        right.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> key[i] >> left[i] >> right[i];
        }
    }

    /**
     * Function to return in-order traversed values of BST.
     * @return vector of int denoting traversed values.
     **/
    vector<int> in_order() {
        vector<int> result;
        in_order_util(0, result);
        return result;
    }

    /**
     * Function to return pre-order traversed values of BST.
     * @return vector of int denoting traversed values.
     **/
    vector<int> pre_order() {
        vector<int> result;
        pre_order_util(0, result);

        return result;
    }

    /**
     * Function to return post-order traversed values of BST.
     * @return vector of int denoting traversed values.
     **/
    vector<int> post_order() {
        vector<int> result;
        post_order_util(0, result);

        return result;
    }
};

/**
 * Function to print elements of vector separated by space.
 * @param a vector to be printed.
 **/
void print(vector<int> a) {
    for (size_t i = 0; i < a.size(); i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';
}

int main_with_large_stack_space() {
    ios_base::sync_with_stdio(0);
    TreeOrders t;
    t.read();
    print(t.in_order());
    print(t.pre_order());
    print(t.post_order());
    return 0;
}

int main(int argc, char **argv) {
#if defined(__unix__) || defined(__APPLE__)
    // Allow larger stack space
    const rlim_t kStackSize = 16 * 1024 * 1024;  // min stack size = 16 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0) {
        if (rl.rlim_cur < kStackSize) {
            rl.rlim_cur = kStackSize;
            result      = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0) {
                std::cerr << "setrlimit returned result = " << result
                          << std::endl;
            }
        }
    }
#endif

    return main_with_large_stack_space();
}
