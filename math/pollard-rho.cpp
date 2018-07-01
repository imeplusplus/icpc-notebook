// Pollard Rho - Integer factoring O(n^1/4)
// requires n to be composite (use Miller Rabin to test)
ll pollard(ll n) {
  ll x, y, d, c = 1;
  if (n%2==0) return 2;
  while (1) {
    y = x = 2;
    while (1) {
      x = mulmod(x,x,n); x = (x-c)%n;
      y = mulmod(y,y,n); y = (y-c)%n;
      y = mulmod(y,y,n); y = (y-c)%n;
      d = gcd(abs(n+y-x), n);
      if (d == n) break;
      else if (d > 1) return d;
    }
    c++;
  }
}

// Factorize number using pollar
void fator(ll n, vector<ll>& v) {
  if (isprime(n)) { v.pb(n); return; }                                                                                     ll f = pollard(n);
  ll f = pollard(n);
  factorize(f, v); factorize(n/f, v);
}
