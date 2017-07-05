// Lowest Common Ancestor <O(nlogn), O(logn)>
int anc[25][N], h[N], rt;

// build (sancse table)
anc[0][rt] = rt; // set ancent of the root to itself
for (int i = 0; (1<<i) < n; ++i)
  for (int j = 1; j <= n; ++j)
    anc[i][j] = anc[i-1][anc[i-1][j]];

// query
int lca(int u, int v) {
  if (h[u] < h[v]) swap(u, v);
  for (int i = 20; i >= 0; --i) if (h[u]-(1<<i) <= h[v])
    u = anc[i][u];
  if (u == v) return u;
  for (int i = 20; i >= 0; --i) if (anc[i][u] != anc[i][v])
    u = anc[i][u], v = anc[i][v];
  return anc[0][u];
}
