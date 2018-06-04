// TODO: retest this code. It was tested once, but had to be pushed for backup purposes.
// DO TEST IT BEFORE PROPER USE.

// Tarjan for SCC and Edge Biconnected Componentes - O(n + m)
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+5;

vector<int> adj[N], st;
int num[N], low[N], vis[N], cnt, scc[N], sccn=1;

void dfs(int u, int p) {
  num[u] = low[u] = ++cnt;
  int ch = 0;
  st.push_back(u), vis[u] = 1;

  for(int v : adj[u]) {
    if (!num[v]) dfs(v, u);
    // Uncomment below for biconnected components.
    if (vis[v]/* and v != p*/) low[u] = min(low[u], low[v]);
  }

  if (low[u] == num[u]) while(1) {
      int v = st.back(); st.pop_back();
      scc[v] = sccn, vis[v] = 0;
      if (v == u) { sccn++; break; }
  }
}

void tarjan(int n) { for(int i=1; i<=n; ++i) if (!num[i]) dfs(i, -1); }
