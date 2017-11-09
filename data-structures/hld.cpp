// Heavy-Light Decomposition
vector<int> adj[N];
int par[N], h[N];

int chainno, chain[N], head[N], chainpos[N], chainsz[N], pos[N], arrsz;
int sc[N], sz[N];

void dfs(int u) {
  sz[u] = 1, sc[u] = 0; // nodes 1-indexed (0-ind: sc[u]=-1)
  for (int v : adj[u]) if (v != par[u]) {
    par[v] = u, h[v] = h[u]+1, dfs(v);
    sz[u]+=sz[v];
    if (sz[sc[u]] < sz[v]) sc[u] = v; // 1-indexed (0-ind: sc[u]<0 or ...)
  }
}

void hld(int u) {
  if (!head[chainno]) head[chainno] = u; // 1-indexed
  chain[u] = chainno;
  chainpos[u] = chainsz[chainno];
  chainsz[chainno]++;
  pos[u] = ++arrsz;

  if (sc[u]) hld(sc[u]);

  for (int v : adj[u]) if (v != par[u] and v != sc[u])
    chainno++, hld(v);
}

int lca(int u, int v) {
  while (chain[u] != chain[v]) {
    if (h[head[chain[u]]] < h[head[chain[v]]]) swap(u, v);
    u = par[head[chain[u]]];
  }
  if (h[u] > h[v]) swap(u, v);
  return u;
}

int query_up(int u, int v) {
  if (u == v) return 0;
  int ans = -1;
  while (1) {
    if (chain[u] == chain[v]) {
      if (u == v) break;
      ans = max(ans, query(1, 1, n, chainpos[v]+1, chainpos[u]));
      break;
    }

    ans = max(ans, query(1, 1, n, chainpos[head[chain[u]]], chainpos[u]));
    u = par[head[chain[u]]];
  }
  return ans;
}

int query(int u, int v) {
  int l = lca(u, v);
  return max(query_up(u, l), query_up(v, l));
}
