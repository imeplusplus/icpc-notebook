// Kosaraju - SCC O(V+E)
// For undirected graph uncomment lines below

vector<int> adj[N], adjt[N];
int n, ordn, cnt, vis[N], ord[N], cmp[N];
//int par[N];

// add edge u -> v
void add_edge(int u, int v){
  adj[u].push_back(v);
  adjt[v].push_back(u);
}

void dfs(int u) {
  vis[u] = 1;
  for (auto v : adj[u]) if (!vis[v]) dfs(v);
  // for (auto v : adj[u]) if(!vis[v]) par[v] = u, dfs(v);
  ord[ordn++] = u;
}

void dfst(int u) {
  cmp[u] = cnt, vis[u] = 0;
  for (auto v : adjt[u]) if (vis[v]) dfst(v);
  // for (auto v : adj[u]) if(vis[v] and u != par[v]) dfst(v);
}

// in main
for (int i = 1; i <= n; ++i) if (!vis[i]) dfs(i);
for (int i = ordn-1; i >= 0; --i) if (vis[ord[i]]) cnt++, dfst(ord[i]);
