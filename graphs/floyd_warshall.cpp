/**********************************************************************************
* FLOYD-WARSHALL ALGORITHM (SHORTEST PATH TO ANY VERTEX)                          *
* Time complexity: O(V^3)                                                         *
* Usage: dist[from][to]                                                           *
* Notation: m:           number of edges                                          *
*           n:           number of vertices                                       *
*           (a, b, w):   edge between a and b with weight w                       *
**********************************************************************************/

int adj[N][N]; // no-edge = INF

for (int k = 0; k < n; ++k)
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      adj[i][j] = min(adj[i][j], adj[i][k]+adj[k][j]);
