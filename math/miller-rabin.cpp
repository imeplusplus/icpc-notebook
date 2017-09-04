// Miller-Rabin - Primarily Test O(k*logn*logn*logn)
bool miller(ll n, ll a) {
  if (a >= n) return 1;
  ll s = 0, d = n-1;
  while (d%2 == 0 and d) d >>= 1, s++;
  ll x = fexp(a, d, n);
  if (x == 1 or x == n-1) return 1;
  for (int r = 0; r < s; r++, x = mulmod(x,x,n)) {
    if (x == 1) return 0;
    if (x == n-1) return 1;
  }
  return 0;
}

bool isprime(ll n) {
  int base[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
  for (int i = 0; i < 12; ++i) if (!miller(base[i], n)) return 0;
  return 1;
}
