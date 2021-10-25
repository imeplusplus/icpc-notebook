/**********************************************************************************
* DFS (DEPTH-FIRST SEARCH)                                                        *
* Time complexity: O(V+E)                                                         *                                                      *
* Notation: adj[x]: adjacency list for node x                                     *
*           vis[i]: visited state for node i (0 or 1)                             *
**********************************************************************************/

const int N = 1e5+10;
int vis[N];
vector<int> adj[N];

void dfs(int u) {
  vis[u] = 1;
  for (int v : adj[u]){
    if (!vis[v]) {
        dfs(v);
    }
  }
    // vis[u] = 0;
    // Uncomment the line above if you need to
    // traverse only one path at a time (backtracking)
}