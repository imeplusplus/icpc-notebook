// Fenwick Tree / Binary Indexed Tree
int bit[N];

void add(int p, int v) {
  for (p+=2; p<N; p+=p&-p) bit[p] += v;
}

int query(int p) {
  int r = 0;
  for (p+=2; p; p-=p&-p) r += bit[p];
  return r;
}
