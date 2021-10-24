// Disjoint Set Union / Union-find
// Unite - O(alpha n)
// Find - O(alpha n)

int par[N], sz[N];

int find(int a) { return par[a] == a ? a : par[a] = find(par[a]); }

void unite(int a, int b) {
  if ((a = find(a)) == (b = find(b))) return;
  if (sz[a] < sz[b]) swap(a, b);
  par[b] = a; sz[a] += sz[b];
}

// in main
for (int i = 1; i <= n; i++) par[i] = i, sz[i] = 1;
