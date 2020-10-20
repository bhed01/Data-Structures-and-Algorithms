#include <iostream>
#include <vector>
#define PRIME 1000000007
#define MULT 31

using namespace std;

size_t xloockup[100001];
size_t pre_hash_text[200001];
size_t pre_hash_patt[100001];
string text;
string pattern;

long long power(size_t x, size_t y, size_t m) {
    if (y == 0)
        return 1;
    long long p = power(x, y / 2, m) % m;
    p           = (p * p) % m;
    return (y % 2 == 0) ? p : (x * p) % m;
}

size_t hash_func(const string &s) {
    unsigned long long hash = 0;
    for (long long i = static_cast<long long>(s.size()) - 1; i >= 0; --i)
        hash = (hash * MULT + s[i]) % PRIME;
    return hash;
}

size_t hash_func(size_t hash1, size_t hash2, size_t len) {
    long long y = (hash1 - (hash2 * xloockup[len]) % PRIME + PRIME) % PRIME;
    return y;
}

size_t hash_func(size_t pre_hash, char ne) {
    return ((MULT * pre_hash) % PRIME + ne) % PRIME;
}

long long binarySearch(long long start_t, long long start, long long end, long long k, long long count) {
    long long mid{start + (end - start) / 2};
    long long mid_t{start_t + mid};
    long long count_err{0};
    if (start <= end) {
        if (text[mid_t] != pattern[mid])
            count++;
        if (count <= k) {
            bool left_mismatch  = hash_func(pre_hash_text[start_t + start],
                                           pre_hash_text[mid_t],
                                           mid_t - start_t - start) != hash_func(pre_hash_patt[start],
                                                                                 pre_hash_patt[mid],
                                                                                 mid - start);
            bool right_mismatch = hash_func(pre_hash_text[mid_t + 1],
                                            pre_hash_text[start_t + end + 1],
                                            start_t + end - mid_t) != hash_func(pre_hash_patt[mid + 1],
                                                                                pre_hash_patt[end + 1],
                                                                                end - mid);
            if (left_mismatch && right_mismatch) {
                if (count + 2 <= k) {
                    count = binarySearch(start_t, start, mid - 1, k, count);
                    if (count + 1 <= k)
                        count = binarySearch(start_t, mid + 1, end, k, count);
                    else
                        count_err = 1;
                } else {
                    count_err = 2;
                }
            } else if (left_mismatch) {
                if (count + 1 <= k)
                    count = binarySearch(start_t, start, mid - 1, k, count);
                else {
                    count_err = 1;
                }

            } else if (right_mismatch) {
                if (count + 1 <= k)
                    count = binarySearch(start_t, mid + 1, end, k, count);
                else {
                    count_err = 1;
                }
            }
        }
    }
    return count + count_err;
}

vector<int> solve(int k) {
    vector<int> pos;

    long long m = text.length();
    long long n = pattern.length();

    pre_hash_text[m]     = 0;
    pre_hash_text[m - 1] = hash_func(text.substr(m - 1, 1));
    pre_hash_patt[n]     = 0;
    pre_hash_patt[n - 1] = hash_func(pattern.substr(n - 1, 1));

    for (long long i{(long long)m - 2}; i >= 0; i--) {
        pre_hash_text[i] = hash_func(pre_hash_text[i + 1], text[i]);
    }
    for (long long i{(long long)n - 2}; i >= 0; i--) {
        pre_hash_patt[i] = hash_func(pre_hash_patt[i + 1], pattern[i]);
    }

    for (long long i{}; i < m - n + 1; i++) {
        if (k >= binarySearch(i, 0, n - 1, k, 0))
            pos.push_back(i);
    }

    return pos;
}

int main() {
    xloockup[0] = 1;
    for (size_t i{1}; i < 100001; i++) {
        xloockup[i] = (xloockup[i - 1] * MULT) % PRIME;
    }

    ios_base::sync_with_stdio(false), cin.tie(0);
    int k;
    while (cin >> k >> text >> pattern) {
        auto a = solve(k);
        cout << a.size();
        for (int x : a)
            cout << " " << x;
        cout << "\n";
    }
}
