// Breadth First Search O(V+E)
int dist[N];
cl(dist,63);

queue<int> q;
q.push(1);
d[1] = 0;

while (!q.empty()) {
  int u = q.front(); q.pop();
  for (int v : adj[u]) if (d[v] == INF)
    d[v] = d[u]+1, q.push(v);
}
