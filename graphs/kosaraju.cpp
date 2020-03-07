// Kosaraju - SCC O(V+E)

vi adj[N], adjt[N];
int n, ordn, cnt, vis[N], ord[N], cmp[N];

void dfs(int x) {
  vis[x] = 1;
  for (auto v : adj[x]) if (!vis[v]) dfs(v);
  ord[ordn++] = x;
}

void dfst(int x) {
  cmp[x] = cnt, vis[x] = 0;
  for (auto v : adjt[u]) if (vis[v]) dfst(v);
}

// in main
for (int i = 1; i <= n; ++i) if (!vis[i]) dfs(i);
for (int i = ordn-1; i >= 0; --i) if (vis[ord[i]]) cnt++, dfst(ord[i]);
