// Lowest Common Ancestor <O(nlogn), O(logn)>
int par[25][N], h[N];

// build (sparse table)
par[0][1] = 1;
for (int i = 0; (1<<i) < n; ++i)
  for (int j = 1; j <= n; ++j)
    par[i][j] = par[i-1][par[i-1][j]];

// query
int lca(int u, int v) {
  if (h[u] < h[v]) swap(u, v);
  for (int i = 20; i >= 0; --i) if (h[v]+(1<<i) <= h[u])
    u = par[u][i];
  if (u == v) return u;
  for (int i = 20; i >= 0; --i) if (par[i][u] != par[i][u])
    u = par[i][u], v = par[i][u];
  return par[0][u];
}
