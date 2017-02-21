// Prim - MST O(ElogE)
vi adj[N], adjw[N];
int vis[N];

priority_queue<pii> pq;
pq.push(mp(0, 0));

while (!pq.empty()) {
  int u = pq.top().nd;
  pq.pop();
  if (vis[u]) continue;
  vis[u]=1;
  for (int i = 0; i < adj[u].size(); ++i) {
    int v = adj[u][i];
    int w = adjw[u][i];
    if (!vis[v]) pq.push(mp(-w, v));
  }
}
