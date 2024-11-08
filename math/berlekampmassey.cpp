#include <bits/stdc++.h>
// #include <chrono>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

#define endl '\n'
#define double long double
#define int long long

const int mod = 998244353;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template <int mod = (int)1e9 + 7> struct modint {
    int x;
    modint(int y = 0) : x((y % mod + mod) % mod) { }
    friend modint operator ^ (modint a, long long b) {
        modint r = 1;
        for(; b; b >>= 1, a *= a) {
            if(b & 1) {
                r *= a;
            } 
        }
        return r;
    }
    friend modint operator - (modint a) {
        return modint(0) - a;
    }
    friend modint operator ! (modint a) {
        return a ^ (mod - 2);
    }
    modint& operator /= (modint const& b) {
        return *this *= !b;
    }
    friend modint operator + (modint a, modint const& b) {
        return a += b;
    }
    friend modint operator - (modint a, modint const& b) {
        return a -= b;
    }
    friend modint operator * (modint a, modint const& b) {
        return a *= b;
    }
    friend modint operator / (modint a, modint const& b) {
        return a /= b;
    }
    friend bool operator != (const modint &a, const modint b) {
        return a.x != b.x;
    }
    friend bool operator == (const modint &a, const modint b) {
        return a.x == b.x;
    }
    modint& operator *= (modint const& b) {
        x = 1ll * x * b.x % mod;
        return *this;
    }
    friend ostream& operator << (ostream& os, modint const& a) {
        return os << a.x;
    }
    modint& operator += (modint const& b) {
        x += b.x;
        x = (x >= mod) ? x - mod : x;
        return *this;
    }
    modint& operator -= (modint const& b) {
        x = x >= b.x ? x - b.x : x - b.x + mod;
        return *this;
    }
};

using mint = modint<mod>;


template<typename T>
vector<T> berlekampMassey(const vector<T> &s) {
    vector<T> c;    // the linear recurrence sequence we are building
    vector<T> oldC; // the best previous version of c to use (the one with the rightmost left endpoint)
    int f = -1;     // the index at which the best previous version of c failed on
    for (int i=0; i<(int)s.size(); i++) {
        // evaluate c(i)
        // delta = s_i - \sum_{j=1}^n c_j s_{i-j}
        // if delta == 0, c(i) is correct
        T delta = s[i];
        for (int j=1; j<=(int)c.size(); j++)
            delta -= c[j-1] * s[i-j];   // c_j is one-indexed, so we actually need index j - 1 in the code
        if (delta == 0)
            continue;   // c(i) is correct, keep going
        // now at this point, delta != 0, so we need to adjust it
        if (f == -1) {
            // this is the first time we're updating c
            // s_i was the first non-zero element we encountered
            // we make c of length i + 1 so that s_i is part of the base case
            c.resize(i + 1);
            f = i;
        } else {
            // we need to use a previous version of c to improve on this one
            // apply the 5 steps to build d
            // 1. set d equal to our chosen sequence
            vector<T> d = oldC;
            // 2. multiply the sequence by -1
            for (T &x : d)
                x = -x;
            // 3. insert a 1 on the left
            d.insert(d.begin(), 1);
            // 4. multiply the sequence by delta / d(f + 1)
            T df1 = 0;  // d(f + 1)
            for (int j=1; j<=(int)d.size(); j++)
                df1 += d[j-1] * s[f+1-j];
            assert(df1 != 0);
            T coef = delta / df1;   // storing this in outer variable so it's O(n^2) instead of O(n^2 log MOD)
            for (T &x : d)
                x *= coef;
            // 5. insert i - f - 1 zeros on the left
            vector<T> zeros(i - f - 1);
            zeros.insert(zeros.end(), d.begin(), d.end());
            d = zeros;
            // now we have our new recurrence: c + d
            vector<T> temp = c; // save the last version of c because it might have a better left endpoint
            c.resize(max(c.size(), d.size()));
            for (int j=0; j<(int)d.size(); j++)
                c[j] += d[j];
            // finally, let's consider updating oldC
            if (i - (int) temp.size() > f - (int) oldC.size()) {
                // better left endpoint, let's update!
                oldC = temp;
                f = i;
            }
        }
    }
    return c;
}

main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<mint> v;
    vector<mint> rnd;
    for(int i = 0; i < 10; i++) {
        rnd.push_back(rand() % mod);
    }
    for(int i = 0; i < 10; i++) {
        v.push_back(rnd[i]);
    }
    for(int i = 0; i < 10; i++) {
        mint sum = 0;
        for(int j = 0; j < 10; j++) {
            sum += rnd[9 - j] * v[i + j];
        }
        v.push_back(sum);
    }
    vector<mint> c = berlekampMassey(v);
    for(auto x : rnd) {
        cout << x << " ";
    }
    cout << endl;
    for(auto x : c) {
        cout << x << " ";
    }
}
