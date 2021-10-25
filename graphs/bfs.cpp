/**********************************************************************************
* BFS (BREADTH-FIRST SEARCH)                                                      *
* Time complexity: O(V+E)                                                         *
* Usage: bfs(node)                                                                *
* Notation: s: starting node                                                      *
*           adj[i]: adjacency list for node i                                     *
*           vis[i]: visited state for node i (0 or 1)                             *
**********************************************************************************/

const int N = 1e5+10; // Maximum number of nodes
int dist[N], par[N];
vector <int> adj[N];
queue <int> q;

void bfs (int s) {
    memset(dist, 63, sizeof(dist));
    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v : adj[u]) if (dist[v] > dist[u] + 1) {
            par[v] = u;
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
}