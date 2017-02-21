struct edge {int a, b, c, f;};

int n, s, t, h[N], ptr[N];
vector<edge> e;
vector<int> g[N];

void add_edge (int a, int b, int c) {
  int k = e.size();
  e.push_back({a, b, c, 0});
  e.push_back({b, a, 0, 0});
  g[a].push_back(k);
  g[b].push_back(k+1);
}

bool bfs() {
  memset(h, 63, sizeof(h));
  queue<int> q;
  q.push(s);
  h[s] = 0;
  while(!q.empty()) {
    int u = q.front(); q.pop();
    for(int i : g[u]) {
      int v = e[i].b;
      if (e[i].f < e[i].c)
        q.push(v), h[v] = h[u] + 1;
    }
  }
  return h[t] != -1;
}

int dfs (int u, int flow) {
  if (!flow) return 0;
  if (u == t) return flow;
  for (int& i = ptr[u]; i < g[u].size(); ++i) {
    edge& dir = e[g[u][i]], rev = e[g[u][i^1]];
    int v = dir.b;

    if (h[v] != h[u] + 1)  continue;
    int inc = dfs(v, min(flow, dir.c - dir.f));
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
    memset (ptr, 0, n * sizeof ptr[0]);
    while (int inc = dfs(s, INF)) flow += inc;
  }
  return flow;
}
