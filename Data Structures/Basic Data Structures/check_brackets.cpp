/**
 * The goal of this problem is to implement a feature to find errors in the
 * usage of brackets in the code.
 * @file check_brakcets.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 */
#include <iostream>
#include <stack>
#include <string>

/**
 * Sturcture to store the type of bracket and position of the bracket.
 **/
struct Bracket {
    Bracket(char type, int position) : type(type), position(position) {}

    /**
     * Checks whether char 'c' matches with the type of bracket.
     * @param c char to be matched.
     * @return true if matched else false.
     **/
    bool Matchc(char c) {
        if (type == '[' && c == ']') return true;
        if (type == '{' && c == '}') return true;
        if (type == '(' && c == ')') return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);
    std::stack<Bracket> opening_brackets_stack;

    bool error = false;
    int pos{};
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            opening_brackets_stack.push(Bracket(next, position + 1));
        } else if (next == ')' || next == ']' || next == '}') {
            if (!opening_brackets_stack.empty()) {
                if (opening_brackets_stack.top().Matchc(next)) {
                    opening_brackets_stack.pop();
                } else {
                    error = true;
                    pos = position + 1;
                    break;
                }
            } else {
                error = true;
                pos = position + 1;
                break;
            }
        }
    }
    if (!opening_brackets_stack.empty() && !error) {
        error = true;
        pos = opening_brackets_stack.top().position;
    }
    if (error) {
        std::cout << pos << std::endl;
    } else {
        std::cout << "Success" << std::endl;
    }

    return 0;
}
