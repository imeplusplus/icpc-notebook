/**********************************************************************************
* BELLMAN-FORD ALGORITHM (SHORTEST PATH TO A VERTEX - WITH NEGATIVE COST)         *
* Time complexity: O(VE)                                                          *
* Usage: dist[node]                                                               *
* Notation: m:           number of edges                                          *
*           n:           number of vertices                                       *
*           (a, b, w):   edge between a and b with weight w                       *
*           s:           starting node                                            *
**********************************************************************************/
const int N = 1e4+10; // Maximum number of nodes
vector<int> adj[N], adjw[N];
int dist[N], v, w;

memset(dist, 63, sizeof(dist));
dist[0] = 0;
for (int i = 0; i < n-1; ++i)
	for (int u = 0; u < n; ++u)
		for (int j = 0; j < adj[u].size(); ++j)
			v = adj[u][j], w = adjw[u][j],
			dist[v] = min(dist[v], dist[u]+w);
