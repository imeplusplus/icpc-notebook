// Persistent Segtree
// Memory: O(n logn)
// Operations: O(log n)
int l[N], r[N], st[N], ls[N], rs[N], id[N], stsz;

// Returns root of initial tree.
// i and j are the first and last elements of the tree.
int init(int i, int j) {
  int v = ++stsz;
  l[v] = i, r[v] = j;

  if (i != j) {
    ls[v] = init(i, (i+j)/2);
    rs[v] = init((i+j)/2+1, j);
    st[v] = /* calculate value from rs[v] and ls[v] */;
  } else {
    st[v] = /* insert initial value here */;
  }

  return v;
}

// Gets the sum from i to j from tree with root u
int sum(int u, int i, int j) {
  if (j < l[u] or r[u] < i) return 0;
  if (i <= l[u] and r[u] <= j) return st[u];
  return sum(ls[u], i, j) + sum (rs[u], i, j);
}

// Copies node j into node i
void clone(int i, int j) {
  l[i] = l[j], r[i] = r[j];
  st[i] = st[j];
  ls[i] = ls[j], rs[i] = rs[j];
}

// Sums v to index i from the tree with root u
int update(int u, int i, int v) {
  if (i < l[u] or r[u] < i) return u;

  clone(++stsz, u);
  u = stsz;
  ls[u] = update(ls[u], i, v);
  rs[u] = update(rs[u], i, v);

  if (l[u] == r[u]) st[u] += v;
  else st[u] = st[ls[u]] + st[rs[u]];

  return u;
}
