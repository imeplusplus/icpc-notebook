// O(sqrt(p))
// Find integer k >= 0 such that a^k = m mod(p) or return -1 if not possible
// Works just for p prime and gives one arbitrary solution.
// For a stronger (and larger) algorithm use the second function.
ll discrete_log(ll a, ll m, ll p) {
  unordered_map<ll, ll> babystep;

  ll b = 1, an = a;
  // set b to the ceil of sqrt(p):
  while(b*b < p) b++, an = (an * a) % p;

  // babysteps:
  ll bstep = m;
  for(ll i=0; i<=b; i++) {
    babystep[bstep] = i;
    bstep = (bstep * a) % p;
  }

  // giantsteps:
  ll gstep = an;
  for(ll i=1; i<=b; i++) {
    if(babystep.count(gstep)) {
      return (b * i - babystep[gstep]);
    }
    gstep = (gstep * an) % p;
  }

  return -1;
}

// O(sqrt(m))
// Solve c * a^x = b mod(m) for integer x >= 0.
// Return {x, y} where x and y are solutions.
// If {-1, -1} it means that there are no solutions.
// If {x, -1} it means that x is the only solution.
// If {x, y} it means that x + k * (y - x) for k >= 0 are all the solutions.
// Works for any integer values of c, a, b and positive m
pll discrete_log(ll c, ll a, ll b, ll m){
  pll r = {-1, -1};
  c = ((c % m) + m) % m, a = ((a % m) + m) % m, b = ((b % m) + m) % m;
  if(c == b)
    r.st = 0;
  
  ll g = __gcd(a, m);
  if(b % g) return r;
  
  if(g > 1){
    pll h = discrete_log(c * a / g, a, b / g, m / g);
    if(r.st == 0) r.nd = h.st + (h.st >= 0);
    else r = {h.st + (h.st >= 0), h.nd + (h.nd >= 0)};
    return r;
  }
  
  unordered_map<ll, ll> babystep[2];
  ll n = 1, an = a % m;
  
  // set n to the ceil of sqrt(m):
  while(n * n < m) n++, an = (an * a) % m;

  // babysteps:
  ll bstep = b;
  for(ll i = 0; i <= n; i++){
    if(babystep[0].find(bstep) != babystep[0].end())
    	babystep[1][bstep] = babystep[0][bstep];
    babystep[0][bstep] = i;
    bstep = (bstep * a) % m;
  }

  // giantsteps:
  ll gstep = c * an % m;
  for(ll i = 1; i <= n; i++){
    for(int j = 0; j < 2; j++){
      if(babystep[j].find(gstep) != babystep[j].end()){
        ll h = n * i - babystep[j][gstep];
        if(r.st < 0 || r.st > h){
          r.nd = r.st;
          r.st = h;
	    }
	    else if(r.st != h && (r.nd < 0 || r.nd > h)) r.nd = h;
      }
    }
	gstep = (gstep * an) % m;
  }
  return r;
}
