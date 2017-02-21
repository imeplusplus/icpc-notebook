// Suffix Array O(nlogn)
char s[N];
int n, r, ra[N], sa[N], tra[N], tsa[N], c[N]; // n = strlen(s)

void count(int k) {
  int sum = 0, x = max(300, n); cl(c, 0);
  for (int i = 0; i < n; ++i) c[i+k<n ? ra[i+k] : 0]++;
  for (int i = 0; i < x; ++i) sum += c[i], c[i] = sum-c[i];
  for (int i = 0; i < n; ++i) tsa[c[sa[i]+k<n ? ra[sa[i]+k] : 0]++] = sa[i];
  for (int i = 0; i < n; ++i) sa[i] = tsa[i];
}

void suffixarray() {
  for (int i = 0; i < n; ++i) ra[i] = s[i], sa[i] = i;
  for (int k = 1; k < n; k <<= 1) {
    count(k); count(0);
    tra[sa[0]] = r = 0;
    for (int i = 1; i < n; ++i)
      tra[sa[i]] = (ra[sa[i]] == ra[sa[i-1]] and ra[sa[i]+k] == ra[sa[i-1]+k]) ? r : ++r;
    for (int i = 0; i < n; ++i) ra[i] = tra[i];
    if (ra[sa[n-1]] == n-1) break;
  }
}

// String matching with SA O(mlogn)
int mlo, mhi;
int match(char p[], int m) {
  int lo = 0, hi = n-1;
  while (lo < hi) {
    int mid = (lo+hi)/2;
    int res = strncmp(s+sa[mid], p, m);
    if (res < 0) lo = mid+1;
    else hi = mid;
  }
  if (strncmp(s+sa[lo], p, m)) return 0; // no match
  mlo = lo;

  lo = 0, hi = n-1;
  while (lo < hi) {
    int mid = (lo+hi)/2;
    int res = strncmp(s+sa[mid], p, m);
    if (res <= 0) lo = mid+1;
    else hi = mid;
  }
  if (strncmp(s+sa[hi], p, m)) hi--;
  mhi = hi;
  return 1;
}

// Longest Common Prefix with SA O(n)
int phi[N], plcp[N], lcp[N];
void calcLCP() {
  int l = 0;
  phi[sa[0]] = -1; plcp[sa[0]] = 0;
  for (int i = 1; i < n; ++i) phi[sa[i]] = sa[i-1];
  for (int i = 0; i < n; ++i) {
    if (phi[i] == -1) continue;
    while (s[i+l] == s[phi[i]+l]) l++;
    plcp[i] = l;
    l = max(l-1, 0);
  }
  for (int i = 0; i < n; ++i) lcp[i] = plcp[sa[i]];
}

// Longest Repeated Substring O(n)
int lrs = 0;
for (int i = 0; i < n; ++i) lrs = max(lrs, lcp[i]);

// Longest Common Substring O(n)
// m = strlen(s);
// strcat(s, "$"); strcat(s, p); strcat(s, "#");
// n = strlen(s);
int lcs = 0;
for (int i = 1; i < n; ++i) if ((sa[i] < m) != (sa[i-1] < m))
  lcs = max(lcs, lcp[i]);
