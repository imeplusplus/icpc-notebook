// Kahn - Topological Sort O(V+E)
vi adj[N];
int inc[N]; // number of incoming + outcoming arcs/edges

queue<int> q;
// Watch out for 1-indexed graphs!
for (int i = 0; i < n; ++i) if (inc[i]<=1) q.push(i);

while (!q.empty()) {
  int u = q.front(); q.pop();
  for (int v : adj[u])
    if (inc[v] > 1 and --inc[v] <= 1)
      q.push(v);
}
