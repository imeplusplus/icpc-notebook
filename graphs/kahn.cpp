/**********************************************************************************
* KAHN'S ALGORITHM (TOPOLOGICAL SORTING)                                          *                                                          *
* Time complexity: O(V+E)                                                         *
* Notation: adj[i]:  adjacency matrix for node i                                  *
*           n:       number of vertices                                           *
*           e:       number of edges                                              *
*           a, b:    edge between a and b                                         *
*           inc:     number of incoming arcs/edges                                *
*           q:       queue with the independent vertices                          *
*           tsort:   final topo sort, i.e. possible order to traverse graph       *
**********************************************************************************/


vector <int> adj[N];
int inc[N]; // number of incoming arcs/edges

// undirected graph: inc[v] <= 1
// directed graph:   inc[v] == 0

queue<int> q;
for (int i = 1; i <= n; ++i) if (inc[i] <= 1) q.push(i);

while (!q.empty()) {
  int u = q.front(); q.pop();
  for (int v : adj[u])
    if (inc[v] > 1 and --inc[v] <= 1)
      q.push(v);
}
