// Extended Euclid:
void euclid(ll a, ll b, ll &x, ll &y) {
	if (b) euclid(b, a%b, y, x), y -= x*(a/b);
	else x = 1, y = 0;
}

// find (x, y) such that a*x + b*y = c or return false if it's not possible
// [x + k*b/gcd(a, b), y - k*a/gcd(a, b)] are also solutions
bool diof(ll a, ll b, ll c, ll &x, ll &y){
	euclid(abs(a), abs(b), x, y);
	ll g = abs(__gcd(a, b));
	if(c % g) return false;
	x *= c / g;
	y *= c / g;
	if(a < 0) x = -x;
	if(b < 0) y = -y;
	return true;
}

// auxiliar to find_all_solutions
void shift_solution (ll &x, ll &y, ll a, ll b, ll cnt) {
	x += cnt * b;
	y -= cnt * a;
}

// Find the amount of solutions of
// ax + by = c
// in given intervals for x and y
ll find_all_solutions (ll a, ll b, ll c, ll minx, ll maxx, ll miny, ll maxy) {
	ll x, y, g = __gcd(a, b);
	if(!diof(a, b, c, x, y)) return 0;
	a /= g; b /= g;

	int sign_a = a>0 ? +1 : -1;
	int sign_b = b>0 ? +1 : -1;

	shift_solution (x, y, a, b, (minx - x) / b);
	if (x < minx)
		shift_solution (x, y, a, b, sign_b);
	if (x > maxx)
		return 0;
	int lx1 = x;

	shift_solution (x, y, a, b, (maxx - x) / b);
	if (x > maxx)
		shift_solution (x, y, a, b, -sign_b);
	int rx1 = x;

	shift_solution (x, y, a, b, - (miny - y) / a);
	if (y < miny)
		shift_solution (x, y, a, b, -sign_a);
	if (y > maxy)
		return 0;
	int lx2 = x;

	shift_solution (x, y, a, b, - (maxy - y) / a);
	if (y > maxy)
		shift_solution (x, y, a, b, sign_a);
	int rx2 = x;

	if (lx2 > rx2)
		swap (lx2, rx2);
	int lx = max (lx1, lx2);
	int rx = min (rx1, rx2);

	if (lx > rx) return 0;
	return (rx - lx) / abs(b) + 1;
}

bool crt_auxiliar(ll a, ll b, ll m1, ll m2, ll &ans){
	ll x, y;
	if(!diof(m1, m2, b - a, x, y)) return false;
	ll lcm = m1 / __gcd(m1, m2) * m2;
	ans = ((a + x % (lcm / m1) * m1) % lcm + lcm) % lcm;
	return true;
}

// find ans such that ans = a[i] mod b[i] for all 0 <= i < n or return false if not possible
// ans + k * lcm(b[i]) are also solutions
bool crt(int n, ll a[], ll b[], ll &ans){
	if(!b[0]) return false;
	ans = a[0] % b[0];
	ll l = b[0];
	for(int i = 1; i < n; i++){
	 if(!b[i]) return false;
		if(!crt_auxiliar(ans, a[i] % b[i], l, b[i], ans)) return false;
		l *= (b[i] / __gcd(b[i], l));
	}
	return true;
}
