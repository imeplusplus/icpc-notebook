// Miller-Rabin - Primarily Test O(k*logn*logn*logn)
ll addmod(ll a, ll b, ll m) {
  if(a >= m - b) return a + b - m;
  return a + b;
}

ll mulmod(ll a, ll b, ll m) {
  ll ans = 0;
  while (b) {
    if (b&1) ans=addmod(ans, a, m);
    a=addmod(a, a, m);
    b>>=1;
  }
  return ans;
}

bool miller(ll a, ll n) {
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
  if(n == 1) return 0;
  int base[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
  for (int i = 0; i < 12; ++i) if (!miller(base[i], n)) return 0;
  return 1;
}

//n < 2,047 base = {2};
//n < 1,373,653 base = {2, 3};
//n < 9,080,191 base = {31, 73};
//n < 25,326,001 base = {2, 3, 5};
//n < 3,215,031,751 base = {2, 3, 5, 7};
//n < 4,759,123,141 base = {2, 3, 7, 61};
//n < 1,122,004,669,633 base = {2, 13, 23, 1662803};
//n < 2,152,302,898,747 base = {2, 3, 5, 7, 11};
//n < 3,474,749,660,383 base = {2, 3, 5, 7, 11, 13};
//n < 341,550,071,728,321 base = {2, 3, 5, 7, 11, 13, 17};
//n < 3,825,123,056,546,413,051 base = {2, 3, 5, 7, 11, 13, 17, 19, 23};
//n < 318,665,857,834,031,151,167,461 base = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
//n < 3,317,044,064,679,887,385,961,981 base = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};
