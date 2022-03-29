// factor(N, v) to get N factorized in vector v
// O(N ^ (1 / 4)) on average
// Miller-Rabin - Primarily Test O(|base|*(logn)^2)
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
	while(d % 2 == 0) d >>= 1, s++;
	ll x = fexp(a, d, n);
	if (x == 1 || x == n - 1) return true;
	for (int r = 0; r < s; r++, x = mulmod(x,x,n)){
		if (x == 1) return false;
		if (x == n - 1) return true;
	}
	return false;
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
			if (x == y) break;
			d = __gcd(abs(x-y), n);
			if (d > 1) return d;
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

//n < 2,047 base = {2};
//n < 9,080,191 base = {31, 73};
//n < 2,152,302,898,747 base = {2, 3, 5, 7, 11};
//n < 318,665,857,834,031,151,167,461 base = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
//n < 3,317,044,064,679,887,385,961,981 base = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};
