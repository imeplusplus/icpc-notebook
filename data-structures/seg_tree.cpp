// Segment Tree (Range Query and Range Update)
// Update and Query - O(log n)

int n, v[N], lz[4*N], st[4*N];

void build(int p = 1, int l = 1, int r = n) {
  if (l == r) { st[p] = v[l]; return; }
  build(2*p, l, (l+r)/2);
  build(2*p+1, (l+r)/2+1, r);
  st[p] = min(st[2*p], st[2*p+1]); // RMQ -> min/max, RSQ -> +
}

void push(int p, int l, int r) {
  if (lz[p]) {
    st[p] = lz[p];
    // RMQ -> update: = lz[p],         increment: += lz[p]
    // RSQ -> update: = (r-l+1)*lz[p], increment: += (r-l+1)*lz[p]
    if(l!=r) lz[2*p] = lz[2*p+1] = lz[p]; // update: =, increment +=
    lz[p] = 0;
  }
}

int query(int i, int j, int p = 1, int l = 1, int r = n) {
  push(p, l, r);
  if (l > j or r < i) return INF; // RMQ -> INF, RSQ -> 0
  if (l >= i and j >= r) return st[p];
  return min(query(i, j, 2*p, l, (l+r)/2),
             query(i, j, 2*p+1, (l+r)/2+1, r));
  // RMQ -> min/max, RSQ -> +
}

void update(int i, int j, int v, int p = 1, int l = 1, int r = n) {
  push(p, l, r);
  if (l > j or r < i) return;
  if (l >= i and j >= r) { lz[p] = v; push(p, l, r); return; }
  update(i, j, v, 2*p, l, (l+r)/2);
  update(i, j, v, 2*p+1, (l+r)/2+1, r);
  st[p] = min(st[2*p], st[2*p+1]); // RMQ -> min/max, RSQ -> +
}
