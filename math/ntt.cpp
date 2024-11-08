namespace ntt {
    long long w[N], k, nrev, fact[N], ifact[N];
    void f(int n) {
        fact[0] = 1;
        for(int i = 1; i <= n; i++) {
            fact[i] = (fact[i - 1] * i) % mod;
        }
        ifact[n] = binexp(fact[n], mod - 2);
        for(int i = n - 1; i >= 0; i--) {
            ifact[i] = (ifact[i + 1] * (i + 1)) % mod;
        }
    }
    void init(int n, int root) {
        w[0] = 1;
        k = binexp(root, (mod - 1) / n);
        nrev = binexp(n, mod - 2);
        for(int i = 1; i <= n; i++) {
            w[i] = (w[i - 1] * k) % mod;
        }
    }
    inline void ntt(vector<long long> &a, int n, bool inv = false) {
        a.resize(n);
        for(int i = 0, j = 0; i < n; i++) {
            if(i > j) swap(a[i], a[j]);
            for(int l = n / 2; (j ^= l) < l; l >>= 1);
        }
        for(int i = 2; i <= n; i <<= 1) {
            for(int j = 0; j < n; j += i) {
                for(int l = 0; l < i / 2; l++) {
                    int x = j + l, y = j + l + (i / 2), z = (n / i) * l;
                    long long tmp = (a[y] * w[(inv ? (n - z) : z)]) % mod;
                    a[y] = (a[x] - tmp + mod) % mod;
                    a[x] = (a[j + l] + tmp) % mod;
                }
            }
        }
        if(inv) {
            for(int i = 0; i < n; i++) {
                a[i] = (a[i] * nrev) % mod;
            }
        }
    }
		 // use search() from PrimitiveRoot.cpp if MOD isn't 998244353
    vector<long long> multiply(vector<long long>& a, vector<long long>& b, int root = 3) { 
        int n = a.size() + b.size() - 1;
        while(n & (n - 1)) n++;
        a.resize(n);
        b.resize(n);
        init(n, root);
        ntt(a, n);
        ntt(b, n);
        vector<long long> ans(n);
        for(int i = 0; i < n; i++) {
            ans[i] = (a[i] * b[i]) % mod;
        }
        ntt(ans, n, true);
        return ans;
    }
    vector<long long> poly_shift(vector<long long>& a, int shift) {
        int n = a.size() - 1;
        f(n);
        vector<long long> x(n + 1), y(n + 1);
        long long cur = 1;
        for(int i = 0; i <= n; i++) {
            x[i] = cur * ifact[i] % mod;
            cur = (cur * shift) % mod;
            y[i] = a[n - i] * fact[n - i] % mod;
        }
        vector<long long> tmp = multiply(x, y), res(n + 1);
        for(int i = 0; i <= n; i++) {
            res[i] = tmp[n - i] * ifact[i] % mod;
        }
        return res;
    }
}