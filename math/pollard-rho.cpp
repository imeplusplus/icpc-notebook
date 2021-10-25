// factor(N) return N factorized
// O(N ^ (1 / 4))
ll addmod(ll a, ll b, ll m){
	if(a >= m - b) return a + b - m;
	return a + b;
}

ll mulmod(ll a, ll b, ll m){
	ll ans = 0;
	while(b){
		if(b & 1) ans = addmod(ans, a, m);
		a = addmod(a, a, m);
		b >>= 1;
	}
	return ans;
}

ll fexp(ll a, ll b, ll n){
	ll r = 1;
	while(b){
		if(b & 1) r = mulmod(r, a, n);
		a = mulmod(a, a, n);
		b >>= 1;
	}
	return r;
}

bool miller(ll a, ll n){
	if (a >= n) return true;
	ll s = 0, d = n - 1;
	while(d % 2 == 0 && d) d >>= 1, s++;
	ll x = fexp(a, d, n);
	if (x == 1 || x == n - 1) return true;
	for (int r = 0; r < s; r++, x = mulmod(x,x,n)){
		if (x == 1) return false;
		if (x == n - 1) return true;
	}
	return 0;
}

bool isprime(ll n){
	if(n == 1) return false;
	int base[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
	for (int i = 0; i < 12; ++i) if (!miller(base[i], n)) return false;
	return true;
}

ll pollard(ll n){
	ll x, y, d, c = 1;
	if (n % 2 == 0) return 2;
	while(true){
		y = x = 2;
		while(true){
			x = addmod(mulmod(x,x,n), c, n);
			y = addmod(mulmod(y,y,n), c, n);
			y = addmod(mulmod(y,y,n), c, n);
			d = __gcd(abs(x-y), n);
			if (d == n) break;
			else if (d > 1) return d;
		}
		c++;
	}
}

vector<ll> factor(ll n){
	if (n == 1 || isprime(n)) return {n};
	ll f = pollard(n);
	vector<ll> l = factor(f), r = factor(n / f);
	l.insert(l.end(), r.begin(), r.end());
	sort(l.begin(), l.end());
	return l;
}
