/**
 * The goal of this program is to implement an algorithm to find the longest
 * common substring.
 * @file common_substring.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 **/
#include <iostream>
#include <utility>
#include <vector>
#define PRIME1 1000000007
#define PRIME2 1000000009
#define X1     31
#define X2     97

using namespace std;

/**
 * Funciton to calculate (x^y)%m, where ^ power operator, and % is modulo
 * operator.
 * @param x unsigned long long int
 * @param y unsigned long long int
 * @param m unsigned long long int
 * @return long long int
 **/
long long power(size_t x, size_t y, size_t m) {
    if (y == 0) return 1;
    long long p = power(x, y / 2, m) % m;
    p           = (p * p) % m;
    return (y % 2 == 0) ? p : (x * p) % m;
}

/**
 * Hash function to calculate the hash value of string.
 * @param s string
 * @param x unsigned long long int
 * @param p unsigned long long int
 * @return hash value of the string
 **/
size_t hash_func(const string &s, size_t x, size_t p) {
    size_t hash = 0;
    for (long long i = static_cast<long long>(s.size()) - 1; i >= 0; --i)
        hash = (hash * x + s[i]) % p;
    return hash;
}

/**
 * Hash function to calculate two differnt hash values of a string.
 * @param s string
 * @return pair of two different hash values of string.
 **/
pair<size_t, size_t> hash_func(const string &s) {
    return make_pair(hash_func(s, X1, PRIME1), hash_func(s, X2, PRIME1));
}

/**
 * Hash function to calculate hash value of string using the hash value of
 * previous string.
 * @param pre_hash previous hash value.
 * @param ne new character added to the string.
 * @param old character removed from the string.
 * @param len length of string.
 * @param x hash variable 1
 * @param p hash variable 2
 * @return hash value of the current string.
 **/
size_t hash_func(size_t pre_hash, char ne, char old, size_t len, size_t x,
                 size_t p) {
    long long y = (ne - (old * power(x, len, p)) % p + p) % p;
    return ((x * pre_hash) % p + y) % p;
}

/**
 * Hash function to calculate two differnt hash value of string using the hash
 * value of previous string.
 * @param pre previous hash value pair.
 * @param ne new character added to the string.
 * @param old character removed from the string.
 * @param len length of string.
 * @return pair of two diffent hash values.
 **/
pair<size_t, size_t> hash_func(pair<size_t, size_t> pre, char ne, char old,
                               size_t len) {
    return make_pair(hash_func(pre.first, ne, old, len, X1, PRIME1),
                     hash_func(pre.second, ne, old, len, X2, PRIME1));
}

/**
 * Structure to store starting index of common substring in both the string the
 * length of common substring.
 **/
struct Answer {
    size_t i, j, len;
};

/**
 * Function to find the longest common substring.
 **/
Answer solve(const string &s, const string &t) {
    Answer ans = {0, 0, 0};
    long long l{}, r{(long long)min(s.length(), t.length())};
    while (l <= r) {
        long long k        = l + (r - l) / 2;
        size_t n           = s.length() - k + 1;
        size_t bucket_size = n;
        vector<vector<pair<pair<size_t, size_t>, size_t>>> pre_hash(n);

        pair<size_t, size_t> pre = hash_func(s.substr(n - 1, k));
        pre_hash[pre.first % bucket_size].push_back(make_pair(pre, n - 1));

        for (long long i{(long long)n - 2}; i >= 0; i--) {
            pair<size_t, size_t> temp = hash_func(pre, s[i], s[i + k], k);
            pre_hash[temp.first % bucket_size].push_back(
                make_pair(temp, static_cast<size_t>(i)));
            pre = temp;
        }

        n          = t.length() - k + 1;
        pre        = hash_func(t.substr(n - 1, k));
        size_t ind = pre.first % bucket_size;
        bool found = false;

        for (size_t i{}; i < pre_hash[ind].size(); i++) {
            if (pre_hash[ind][i].first == pre) {
                found = true;
                ans = {pre_hash[ind][i].second, n - 1, static_cast<size_t>(k)};
                break;
            }
        }

        if (!found) {
            for (long long i{(long long)n - 2}; i >= 0; i--) {
                pair<size_t, size_t> temp = hash_func(pre, t[i], t[i + k], k);
                ind                       = temp.first % bucket_size;

                for (size_t j{}; j < pre_hash[ind].size(); j++) {
                    if (pre_hash[ind][j].first == temp) {
                        found = true;
                        ans = {pre_hash[ind][j].second, static_cast<size_t>(i),
                               static_cast<size_t>(k)};
                        break;
                    }
                }

                if (found) break;
                pre = temp;
            }
        }
        if (found)
            l = k + 1;
        else
            r = k - 1;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    string s, t;
    while (cin >> s >> t) {
        auto ans = solve(s, t);
        cout << ans.i << " " << ans.j << " " << ans.len << "\n";
    }
}
