// solve the discrete equation a^k = m mod(p).
// i.e find k such that the equation above is satisfied.
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

  // returns -1 if there isn't any possible value for the answer.
  return -1;
}
