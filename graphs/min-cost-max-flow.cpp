// w: weight or cost, c : capacity
struct edge {int v, f, w, c; };

int node_count, flw_lmt=INF, src, snk, flw, cst, p[N], d[N], et[N];
vector<edge> e;
vector<int> g[N];

void add_edge(int u, int v, int w, int c) {
  int k = e.size();
  node_count = max(node_count, u+1);
  node_count = max(node_count, v+1);
  g[u].push_back(k);
  g[v].push_back(k+1);
  e.push_back({ v, 0,  w, c });
  e.push_back({ u, 0, -w, 0 });
}

void clear() {
  flw_lmt = INF;
  for(int i=0; i<node_count; ++i) g[i].clear();
  e.clear();
  node_count = 0;
}

void min_cost_max_flow() {
  flw = 0, cst = 0;
  while (flw < flw_lmt) {
    memset(et, 0, node_count * sizeof et[0]);
    memset(d, 63, node_count * sizeof d[0]);
    deque<int> q;
    q.push_back(src), d[src] = 0;

    while (!q.empty()) {
      int u = q.front(); q.pop_front();
      et[u] = 2;

      for(int i : g[u]) {
        edge &dir = e[i];
        int v = dir.v;
        if (dir.f < dir.c and d[u] + dir.w < d[v]) {
          d[v] = d[u] + dir.w;
          if (et[v] == 0) q.push_back(v);
          else if (et[v] == 2) q.push_front(v);
          et[v] = 1;
          p[v] = i;
        }
      }
    }

    if (d[snk] > INF) break;

    int inc = flw_lmt - flw;
    for (int u=snk; u != src; u = e[p[u]^1].v) {
      edge &dir = e[p[u]];
      inc = min(inc, dir.c - dir.f);
    }

    for (int u=snk; u != src; u = e[p[u]^1].v) {
      edge &dir = e[p[u]], &rev = e[p[u]^1];
      dir.f += inc;
      rev.f -= inc;
      cst += inc * dir.w;
    }

    if (!inc) break;
    flw += inc;
  }
}
