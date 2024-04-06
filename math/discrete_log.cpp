// O(sqrt(m))
// Solve c * a^x = b mod(m) for integer x >= 0.
// Return the smallest x possible, or -1 if there is no solution
// If all solutions needed, solve c * a^x = b mod(m) and (a*b) * a^y = b mod(m)
// x + k * (y + 1) for k >= 0 are all solutions
// Works for any integer values of c, a, b and positive m

// Corner Cases:
// 0^x = 1 mod(m) returns x = 0, so you may want to change it to -1
// You also may want to change for 0^x = 0 mod(1) to return x = 1 instead
// We leave it like it is because you might be actually checking for m^x = 0^x mod(m)
// which would have x = 0 as the actual solution.
ll discrete_log(ll c, ll a, ll b, ll m){
	c = ((c % m) + m) % m, a = ((a % m) + m) % m, b = ((b % m) + m) % m;
	if(c == b)
		return 0;
	
	ll g = __gcd(a, m);
	if(b % g) return -1;
	
	if(g > 1){
		ll r = discrete_log(c * a / g, a, b / g, m / g);
		return r + (r >= 0);
	}
	
	unordered_map<ll, ll> babystep;
	ll n = 1, an = a % m;
	
	// set n to the ceil of sqrt(m):
	while(n * n < m) n++, an = (an * a) % m;

	// babysteps:
	ll bstep = b;
	for(ll i = 0; i <= n; i++){
		babystep[bstep] = i;
		bstep = (bstep * a) % m;
	}

	// giantsteps:
	ll gstep = c * an % m;
	for(ll i = 1; i <= n; i++){
		if(babystep.find(gstep) != babystep.end())
			return n * i - babystep[gstep];
		gstep = (gstep * an) % m;
	}
	return -1;
}
