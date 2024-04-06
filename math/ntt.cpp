// Number Theoretic Transform - O(nlogn)

// if long long is not necessary, use int instead to improve performance
const int mod = 20*(1<<23)+1;
const int root = 3;

ll w[N];

// a: vector containing polynomial
// n: power of two greater or equal product size
void ntt(ll* a, int n, bool inv) {
	for (int i=0, j=0; i<n; i++) {
		if (i>j) swap(a[i], a[j]);
		for (int l=n/2; (j^=l) < l; l>>=1);
	}

	// TODO: Rewrite this loop using FFT version
	ll k, t, nrev;
	w[0] = 1;
	k = exp(root, (mod-1) / n, mod);
	for (int i=1;i<=n;i++) w[i] = w[i-1] * k % mod;
	for(int i=2; i<=n; i<<=1) for(int j=0; j<n; j+=i) for(int l=0; l<(i/2); l++) {
		int x = j+l, y = j+l+(i/2), z = (n/i)*l;
		t = a[y] * w[inv ? (n-z) : z] % mod;
		a[y] = (a[x] - t + mod) % mod;
		a[x] = (a[j+l] + t) % mod;
	}

	nrev = exp(n, mod-2, mod);
	if (inv) for(int i=0; i<n; ++i) a[i] = a[i] * nrev % mod;
}

// assert n is a power of two greater of equal product size
// n = na + nb; while (n&(n-1)) n++;
void multiply(ll* a, ll* b, int n) {
	ntt(a, n, 0);
	ntt(b, n, 0);
	for (int i = 0; i < n; i++) a[i] = a[i]*b[i] % mod;
	ntt(a, n, 1);
}
