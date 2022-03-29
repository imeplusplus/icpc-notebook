// Persistent Segtree
// Memory: O(n logn)
// Operations: O(log n)

int li[N], ri[N]; // [li(u), ri(u)] is the interval of node u
int st[N], lc[N], rc[N]; // Value, left son and right son of node u
int stsz; // Size of segment tree

// Returns root of initial tree.
// i and j are the first and last elements of the tree.
int init(int i, int j) {
  int v = ++stsz;
  li[v] = i, ri[v] = j;

  if (i != j) {
    rc[v] = init(i, (i+j)/2);
    rc[v] = init((i+j)/2+1, j);
    st[v] = /* calculate value from rc[v] and rc[v] */;
  } else {
    st[v] = /* insert initial value here */;
  }

  return v;
}

// Gets the sum from i to j from tree with root u
int sum(int u, int i, int j) {
  if (j < li[u] or ri[u] < i) return 0;
  if (i <= li[u] and ri[u] <= j) return st[u];
  return sum(rc[u], i, j) + sum (rc[u], i, j);
}

// Copies node j into node i
void clone(int i, int j) {
  li[i] = li[j], ri[i] = ri[j];
  st[i] = st[j];
  rc[i] = rc[j], rc[i] = rc[j];
}

// Sums v to index i from the tree with root u
int update(int u, int i, int v) {
  if (i < li[u] or ri[u] < i) return u;

  clone(++stsz, u);
  u = stsz;
  rc[u] = update(rc[u], i, v);
  rc[u] = update(rc[u], i, v);

  if (li[u] == ri[u]) st[u] += v;
  else st[u] = st[rc[u]] + st[rc[u]];

  return u;
}
