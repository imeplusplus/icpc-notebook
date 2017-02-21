// Miller-Rabin - Primarily Test
bool miller(ll a, ll n) {
  if (a >= n) return 1;
  ll r = 0, s = n-1, j;
  while (s%2==0) s>>=1, r++;
  ll x = fexp(a, s, n);
  if (x == 1) return 1;
  for (j = 0; j < r; ++j, x=mulmod(x,x,n)) if (x==n-1) return 1;
  return 0;
}

bool isprime(ll n) {
  int base[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
  for (int i = 0; i < 12; ++i) if (!miller(base[i], n)) return 0;
  return 1;
}
