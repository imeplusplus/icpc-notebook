// Greatest Common Divisor & Lowest Common Multiple
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a*(b/gcd(a, b)); }

// Multiply caring overflow
ll mulmod(ll a, ll b, ll m=MOD) {
  ll r=1;
  for (a %= m; b; b>>=1, a=(a*2)%m) if (b&1) r=(r+a)%m;
  return r;
}

// Fast exponential
ll fexp(ll a, ll b, ll m=MOD) {
  ll r=1;
  for (; b; b>>=1, a=(a*a)%m) if (b&1) r=(r*a)%m;
  return r;
}

// Catalan
cat[n] = (2*(2*n-1)/(n+1))*cat[n-1]
