// Depth First Search O(V+E)
vi adj[N];
int vis[N];

void dfs(int u) {
  vis[u]=1;
  for (int v : adj[u]) if (!vis[v])
    dfs(v);
}
