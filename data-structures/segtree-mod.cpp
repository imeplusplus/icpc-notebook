// SegTree with mod
// op1 (l, r) -> sum a[i], i = { l .. r }
// op2 (l, r, x) -> a[i] = a[i] mod x, i = { l .. r }
// op3 (idx, x) -> a[idx] = x;

const int N = 1e5 + 5;

struct segTreeNode { ll sum, mx, mn, lz = -1; };

int n, m;
ll a[N];
segTreeNode st[4 * N];

void push(int p, int l, int r) {
  if (st[p].lz != -1) {

    st[p].mx = st[p].mn = st[p].lz;
    st[p].sum = (r - l + 1) * st[p].lz;

    if (l != r) st[2 * p].lz = st[2 * p + 1].lz = st[p].lz;
    st[p].lz = -1;
  }
}

void merge(int p) {
  st[p].mx = max(st[2 * p].mx, st[2 * p + 1].mx);
  st[p].mn = min(st[2 * p].mn, st[2 * p + 1].mn);
  st[p].sum = st[2 * p].sum + st[2 * p + 1].sum;
}

void build(int p = 1, int l = 1, int r = n) {
  if (l == r) {
    st[p].mn = st[p].mx = st[p].sum = a[l];
    return;
  }

  int mid = (l + r) >> 1;
  build(2 * p, l, mid);
  build(2 * p + 1, mid + 1, r);

  merge(p);
}

ll query(int i, int j, int p = 1, int l = 1, int r = n) {
  push(p, l, r);
  if (r < i or l > j) return 0ll;
  if (i <= l and r <= j) return st[p].sum;
  int mid = (l + r) >> 1;
  return query(i, j, 2 * p, l, mid) + query(i, j, 2 * p + 1, mid + 1, r);
}

void module_op(int i, int j, ll x, int p = 1, int l = 1, int r = n) {
  push(p, l, r);
  if (r < i or l > j or st[p].mx < x) return;
  if (i <= l and r <= j and st[p].mx == st[p].mn) {
    st[p].lz = st[p].mx % x;
    push(p, l, r);
    return;
  }
  int mid = (l + r) >> 1;
  module_op(i, j, x, 2 * p, l, mid);
  module_op(i, j, x, 2 * p + 1, mid + 1, r);

  merge(p);
}

void set_op(int i, int j, ll x, int p = 1, int l = 1, int r = n) {
  push(p, l, r);
  if (r < i or l > j) return;
  if (i <= l and r <= j) {
    st[p].lz = x;
    push(p, l, r);
    return;
  }
  int mid = (l + r) >> 1;
  set_op(i, j, x, 2 * p, l, mid);
  set_op(i, j, x, 2 * p + 1, mid + 1, r);

  merge(p);
}
