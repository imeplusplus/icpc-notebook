// Shortest Path Faster Algoritm O(VE)
int dist[N], inq[N];

cl(dist,63);
queue<int> q;
q.push(0); dist[0] = 0; inq[0] = 1;

while (!q.empty()) {
  int u = q.front(); q.pop(); inq[u]=0;
  for (int i = 0; i < adj[u].size(); ++i) {
    int v = adj[u][i], w = adjw[u][i];
    if (dist[v] > dist[u] + w) {
      dist[v] = dist[u] + w;
      if (!inq[v]) q.push(v), inq[v] = 1;
    }
  }
}
