/**
 * The goal of this problem is to implement a stack supporting push(), pop() and
 * max().
 * @file stack_with_max.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 */
#include <algorithm>
#include <cassert>
#include <iostream>
#include <stack>
#include <string>

using std::cin;
using std::cout;
using std::max_element;
using std::stack;
using std::string;

/**
 * Class of Stack with Max functionaliy
 **/
class StackWithMax {
    stack<int> max;  // stack to store only max

   public:
    /**
     * Function to push max of top of stack and 'value'
     * @param value value to be pushed
     **/
    void Push(int value) {
        if (max.empty()) {
            max.push(value);
        } else {
            if (max.top() < value)
                max.push(value);
            else
                max.push(max.top());
        }
    }

    /**
     * Function to pop elements from stack.
     **/
    void Pop() {
        assert(max.size());
        max.pop();
    }

    /**
     * Function to reutrn max of stack
     * @return top of the 'max' stack.
     **/
    int Max() const {
        assert(max.size());
        return max.top();
    }
};

int main() {
    int num_queries = 0;
    cin >> num_queries;

    string query;
    string value;

    StackWithMax s;

    for (int i = 0; i < num_queries; ++i) {
        cin >> query;
        if (query == "push") {
            cin >> value;
            s.Push(std::stoi(value));
        } else if (query == "pop") {
            s.Pop();
        } else if (query == "max") {
            cout << s.Max() << "\n";
        } else {
            assert(0);
        }
    }
    return 0;
}