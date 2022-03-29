// USE INF = 1e9!

/**********************************************************************************
* MIN COST MAX FLOW (MINIMUM COST TO ACHIEVE MAXIMUM FLOW)                        *
* Description: Given a graph which represents a flow network where every edge has *
* a capacity and a cost per unit, find the minimum cost to establish the maximum  *
* possible flow from s to t.                                                      *
* Note: When adding edge (a, b), it is a directed edge!                           *
* Usage: min_cost_max_flow()                                                      *
*        add_edge(from, to, cost, capacity)                                       *
* Notation: flw: max flow                                                         *
*           cst: min cost to achieve flw                                          *
* Testcase:                                                                       *
* add_edge(src, 1, 0, 1);   add_edge(1, snk, 0, 1);   add_edge(2, 3, 1, INF);     *
* add_edge(src, 2, 0, 1);   add_edge(2, snk, 0, 1);   add_edge(3, 4, 1, INF);     *
* add_edge(src, 2, 0, 1);   add_edge(3, snk, 0, 1);                               *
* add_edge(src, 2, 0, 1);   add_edge(4, snk, 0, 1);   => flw = 4, cst = 3         *
**********************************************************************************/

// w: weight or cost, c : capacity
struct edge {int v, f, w, c; };

int n, flw_lmt=INF, src, snk, flw, cst, p[N], d[N], et[N];
vector<edge> e;
vector<int> g[N];

void add_edge(int u, int v, int w, int c) {
  int k = e.size();
  g[u].push_back(k);
  g[v].push_back(k+1);
  e.push_back({ v, 0,  w, c });
  e.push_back({ u, 0, -w, 0 });
}

void clear() {
  flw_lmt = INF;
  for(int i=0; i<=n; ++i) g[i].clear();
  e.clear();
}

void min_cost_max_flow() {
  flw = 0, cst = 0;
  while (flw < flw_lmt) {
    memset(et, 0, (n+1) * sizeof(int));
    memset(d, 63, (n+1) * sizeof(int));
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
