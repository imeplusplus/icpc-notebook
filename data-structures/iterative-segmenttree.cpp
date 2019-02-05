int n; // Array size
int st[2*N];

int query(int a, int b) {
  a += n; b += n;
  int s = 0;
  while (a <= b) {
    if (a%2 == 1) s += st[a++];
    if (b%2 == 0) s += st[b--];
    a /= 2; b /= 2;
  }
  return s;
}

void update(int p, int val) {
  p += n;
  st[p] += val;
  for (p /= 2; p >= 1; p /= 2)
    st[p] = st[2*p]+st[2*p+1];
}
