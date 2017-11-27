// Segment Tree
int st[4*N], v[N], lz[4*N];

void build(int p, int l, int r) {
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

int query(int p, int l, int r, int i, int j) {
  push(p, l, r);
  if (r < i or l > j) return INF; // RMQ -> INF, RSQ -> 0
  if (l >= i and r <= j) return st[p];
  return min(query(2*p, l, (l+r)/2, i, j),
             query(2*p+1, (l+r)/2+1, r, i, j));
  // RMQ -> min/max, RSQ -> +
}

void update(int p, int l, int r, int i, int j, int v) {
  push(p, l, r);
  if (r < i or l > j) return;
  if (l >= i and r <= j) { lz[p] = v; push(p, l, r); return; }
  update(2*p, l, (l+r)/2, i, j, v);
  update(2*p+1, (l+r)/2+1, r, i, j, v);
  st[p] = min(st[2*p], st[2*p+1]); // RMQ -> min/max, RSQ -> +
}
