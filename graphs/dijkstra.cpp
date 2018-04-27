// Dijkstra - SSSP O((V+E)logE)
vi adj[N], adjw[N];
int dist[N];

cl(dist,63);
priority_queue<pii> pq;
pq.push(mp(0,0));

while (!pq.empty()) {
  int u = pq.top().nd;
  int d = -pq.top().st;
  pq.pop();

  if (d > dist[u]) continue;
  for (int i = 0; i < adj[u].size(); ++i) {
    int v = adj[u][i];
    int w = adjw[u][i];
    if (dist[u] + w < dist[v])
      dist[v] = dist[u]+w, pq.push(mp(-dist[v], v));
  }
}
