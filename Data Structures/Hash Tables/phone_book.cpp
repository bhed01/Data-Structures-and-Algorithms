#include <iostream>
#include <string>
#include <unordered_map>

using std::cin;
using std::cout;
using std::string;
using std::unordered_map;

int main() {
    int n;
    cin >> n;
    unordered_map<int, string> record;
    while (n--) {
        string task, name;
        int phone_num;
        cin >> task >> phone_num;
        if (task == "add") {
            cin >> name;
            record[phone_num] = name;
        } else if (task == "find") {
            if (record.count(phone_num) > 0) {
                cout << record[phone_num] << std::endl;
            } else {
                cout << "not found" << std::endl;
            }
        } else {
            record.erase(phone_num);
        }
    }
    return 0;
}