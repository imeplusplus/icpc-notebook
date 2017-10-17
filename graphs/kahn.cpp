// Kahn - Topological Sort O(V+E)

vi adj[N];
int inc[N]; // number of incoming arcs/edges

queue<int> q;
for (int i = 1; i <= n; ++i) if (inc[i]<=1) q.push(i);

while (!q.empty()) {
  int u = q.front(); q.pop();
  for (int v : adj[u])
    // undirected graph: inc[v] <= 1
    // directed graph:   inc[v] == 0
    if (inc[v] > 1 and --inc[v] <= 1)
      q.push(v);
}
