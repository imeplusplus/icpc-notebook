// Persistent Segment Tree
int n;
int rcnt;
int lc[M], rc[M], st[M];

int update(int p, int l, int r, int i, int v) {
  int rt = ++rcnt;
  if (l == r) { st[rt] = v; return rt; }

  int mid = (l+r)/2;
  if (i <= mid) lc[rt] = update(lc[p], l, mid, i, v), rc[rt] = rc[p];
  else          rc[rt] = update(rc[p], mid+1, r, i, v), lc[rt] = lc[p];
  st[rt] = st[lc[rt]] + st[rc[rt]];

  return rt;
}

int query(int p, int l, int r, int i, int j) {
  if (l > j or r < i) return 0;
  if (i <= l and r <= j) return st[p];

  return query(lc[p], l, (l+r)/2, i, j)+query(rc[p], (l+r)/2+1, r, i, j);
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    int a;
    scanf("%d", &a);
    r[i] = update(r[i-1], 1, n, i, 1);
  }

  return 0;
}
