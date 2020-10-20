#include <iostream>
#include <string>
#include <vector>
#define MULTIPLIER 263
#define PRIME 1000000007

using std::string;
typedef unsigned long long ull;

size_t hash_func(const string& s) {
    unsigned long long hash = 0;
    for (long long i = static_cast<long long>(s.size()) - 1; i >= 0; --i)
        hash = (hash * MULTIPLIER + s[i]) % PRIME;
    return hash;
}

long long power(size_t x, size_t y, size_t m) {
    if (y == 0)
        return 1;
    long long p = power(x, y / 2, m) % m;
    p           = (p * p) % m;
    return (y % 2 == 0) ? p : (x * p) % m;
}

size_t hash_func(size_t pre_hash, char ne, char old, size_t len) {
    long long y = (ne - (old * power(MULTIPLIER, len, PRIME)) % PRIME + PRIME) % PRIME;
    return ((MULTIPLIER * pre_hash) % PRIME + y) % PRIME;
}

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<int> get_occurrences(const Data& input) {
    const string &s = input.pattern, t = input.text;
    size_t pat_hash = hash_func(s);
    long long n     = t.length() - s.length() + 1;

    std::vector<int> ans;
    std::vector<size_t> hashes(n);

    hashes[n - 1] = hash_func(t.substr(n - 1, s.length()));
    for (long long i{n - 2}; i >= 0; i--) {
        hashes[i] = hash_func(hashes[i + 1], t[i], t[i + s.length()], s.length());
    }
    for (size_t i = 0; i + s.size() <= t.size(); ++i) {
        if (pat_hash == hashes[i]) {
            if (t.substr(i, s.size()) == s)
                ans.push_back(i);
        }
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
