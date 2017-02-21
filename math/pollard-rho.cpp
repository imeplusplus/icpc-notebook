// Pollard Rho - Integer factoring
ll pollard(ll n) {
  ll x, y, d, c=-1;
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
    c--;
  }
}
