const int N = 2e5 + 5;
int par[N];
vector<int> adj[N];
int sz[N], nxt[N];
int h[N];
int in[N], rin[N], out[N];
int t;

void dfs_sz(int u = 1){
  sz[u] = 1;
  for(auto &v : adj[u]){
    h[v] = h[u] + 1;

    dfs_sz(v);
    sz[u] += sz[v];
    if(sz[v] > sz[adj[u][0]])
      swap(v, adj[u][0]);
  }
}

void dfs_hld(int u = 1){
  in[u] = t++;
  rin[in[u]] = u;
  for(auto v : adj[u]){
    nxt[v] = (v == adj[u][0] ? nxt[u] : v);
    dfs_hld(v);
  }

  out[u] = t - 1;
}

int lca(int u, int v){
  while(nxt[u] != nxt[v]){
    if(h[nxt[u]] < h[nxt[v]]) swap(u, v);
    u = par[nxt[u]];
  }

  if(h[u] > h[v]) swap(u, v);
  return u;
}
