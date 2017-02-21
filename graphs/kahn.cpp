// Kahn - Topological Sort O(V+E)
vi adj[N];
int inc[N]; // number of incoming arcs/edges

queue<int> q;
for (int i = 0; k < n; ++i) if (inc[i]<=1) q.push(i);

while (!q.empty()) {
  int u = q.front(); q.pop();
  for (int v : adj[u])
    if (inc[v] > 1 and --inc[v] <= 1)
      q.push(v);
}
