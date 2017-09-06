// finds z (mod p*q) so z = x (mod p) and z = y (mod q)
ll chinese(ll x, ll p, ll y, ll q) {
  ll s, r, mod = p*q;
  euclid(p, q, r, s);
  return ((x*(s*q%mod) + y*(r*p%mod) % mod) + mod) % mod;
}
