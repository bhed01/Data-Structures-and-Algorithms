#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<vector<string>> hashTable;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime      = 1000000007;
        unsigned long long hash        = 0;
        for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

   public:
    explicit QueryProcessor(int bucket_count) : bucket_count(bucket_count) {
        hashTable.resize(bucket_count);
    }

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            if (hashTable[query.ind].size() == 0) {
                std::cout << std::endl;
            } else {
                for (int i{(int)hashTable[query.ind].size() - 1}; i >= 0; i--) {
                    std::cout << hashTable[query.ind][i] << " ";
                }
                std::cout << std::endl;
            }
        } else {
            size_t hash                 = hash_func(query.s);
            vector<string>::iterator it = std::find(hashTable[hash].begin(),
                                                    hashTable[hash].end(),
                                                    query.s);
            if (query.type == "add") {
                if (it == hashTable[hash].end()) {
                    hashTable[hash].push_back(query.s);
                }
            } else if (query.type == "del") {
                if (it != hashTable[hash].end()) {
                    hashTable[hash].erase(it);
                }
            } else {
                writeSearchResult(it != hashTable[hash].end());
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
