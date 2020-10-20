#include <iostream>
#include <vector>
#define PRIME 1000000007
#define MULTIPLIER 31
using namespace std;

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

size_t hash_func(size_t hash1, size_t hash2, size_t len) {
    long long y = (hash1 - (hash2 * power(MULTIPLIER, len, PRIME)) % PRIME + PRIME) % PRIME;
    return y;
}

size_t hash_func(size_t pre_hash, char ne) {
    return ((MULTIPLIER * pre_hash) % PRIME + ne) % PRIME;
}

class Solver {
    string s;
    vector<size_t> pre_hash;

   public:
    Solver(string s) : s(s) {
        size_t n = s.length();
        pre_hash.resize(n + 1);
        pre_hash[n]     = 0;
        pre_hash[n - 1] = hash_func(s.substr(n - 1, 1));
        for (long long i{(long long)n - 2}; i >= 0; i--) {
            pre_hash[i] = hash_func(pre_hash[i + 1], s[i]);
        }
    }
    bool ask(int a, int b, int l) {
        size_t hash_a = hash_func(pre_hash[a], pre_hash[a + l], l);
        size_t hash_b = hash_func(pre_hash[b], pre_hash[b + l], l);
        if (hash_a == hash_b)
            return true;
        else
            return false;
    }
};

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    string s;
    int q;
    cin >> s >> q;
    Solver solver(s);
    for (int i = 0; i < q; i++) {
        int a, b, l;
        cin >> a >> b >> l;
        cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
    }
}
