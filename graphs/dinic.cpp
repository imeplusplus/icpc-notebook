struct edge {int v, c, f;};

int n, s, t, h[N], ptr[N];
vector<edge> e;
vector<int> g[N];

void add_edge (int a, int b, int c) {
  int k = e.size();
  e.push_back({b, c, 0});
  e.push_back({a, 0, 0});
  g[a].push_back(k);
  g[b].push_back(k+1);
}

bool bfs() {
  memset(h, 0, n * sizeof h[0]);
  queue<int> q;
  h[s] = 1;
  q.push(s);
  while(!q.empty()) {
    int u = q.front(); q.pop();
    for(int i : g[u]) {
      int v = e[i].v;
      if (!h[v] and e[i].f < e[i].c)
        q.push(v), h[v] = h[u] + 1;
    }
  }
  return h[t];
}

int dfs (int u, int flow) {
  if (!flow) return 0;
  if (u == t) return flow;
  for (int &i = ptr[u]; i < g[u].size(); ++i) {
    edge &dir = e[g[u][i]], &rev = e[g[u][i]^1];
    int v = dir.v;
    if (h[v] != h[u] + 1)  continue;
    int inc = min(flow, dir.c - dir.f);
    inc = dfs(v, inc);
    if (inc) {
      dir.f += inc, rev.f -= inc;
      return inc;
    }
  }
  return 0;
}

int dinic() {
  int flow = 0;
  while (bfs()) {
    memset(ptr, 0, n * sizeof ptr[0]);
    while (int inc = dfs(s, INF)) flow += inc;
  }
  return flow;
}
