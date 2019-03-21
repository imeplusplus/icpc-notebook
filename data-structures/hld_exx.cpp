vector<int> adj[N];
int sz[N], nxt[N];
int h[N], par[N];
int in[N], rin[N], out[N];
int t;

void dfs_sz(int u = 1){
  sz[u] = 1;
  for(auto &v : adj[u]) if(v != par[u]) {
    h[v] = h[u] + 1;
    par[v] = u;

    dfs_sz(v);
    sz[u] += sz[v];
    if(sz[v] > sz[adj[u][0]])
      swap(v, adj[u][0]);
  }
}

void dfs_hld(int u = 1){
  in[u] = t++;
  rin[in[u]] = u;
  for(auto v : adj[u]) if(v != par[u]) {
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

int query_up(int u, int v) {
  if(u == v) return 1;
  int ans = 0;
  while(1){
    if(nxt[u] == nxt[v]){
      if(u == v) break;
      ans = max(ans, query(1, 0, n - 1, in[v] + 1, in[u]));
      break;
    }

    ans = max(ans, query(1, 0, n - 1, in[nxt[u]], in[u]));
    u = par[nxt[u]];
  }

  return ans;
}

int hld_query(int u, int v) {
  int l = lca(u, v);
  return mult(query_up(u, l), query_up(v, l));
}
