// Finds a primitive root modulo p
// To make it works for any value of p, we must add calculation of phi(p)
// n is 1, 2, 4 or p^k or 2*p^k (p odd in both cases)
ll root(ll p) {
	ll n = p-1;
	vector<ll> fact;

	for (int i=2; i*i<=n; ++i) if (n % i == 0) {
		fact.push_back (i);
		while (n % i == 0) n /= i;
	}

	if (n > 1) fact.push_back (n);

	for (int res=2; res<=p; ++res) {
		bool ok = true;
		for (size_t i=0; i<fact.size() && ok; ++i)
			ok &= exp(res, (p-1) / fact[i], p) != 1;
		if (ok)  return res;
	}

	return -1;
}
