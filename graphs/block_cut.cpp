// Tarjan for Node Biconnected Componentes - O(n + m)
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+5;

int num[N], low[N], cnt, ch[N], art[N];
int lb[N], bh[N], bn;
int n;

vector<int> adj[N], blc[N], st;

void dfs(int u, int p) {
  num[u] = low[u] = ++cnt;
  ch[u] = adj[u].size();
  st.push_back(u);

  if (adj[u].size() == 1) blc[++bn].push_back(u);

  for(int v : adj[u]) {
    if (!num[v]) {
      dfs(v, u), low[u] = min(low[u], low[v]);
      if (low[v] == num[u]) {
        if (p != -1 or ch[u] > 1) art[u] = 1;
        blc[++bn].push_back(u), bh[bn] = u;
        while(blc[bn].back() != v)
          blc[bn].push_back(st.back()), st.pop_back();
      }
    }
    else if (v != p) low[u] = min(low[u], num[v]), ch[v]--;
  }

  if (low[u] == num[u]) st.pop_back();
}

void tarjan() {
  for(int u=1; u<=n; ++u) if (!num[u]) dfs(u, -1);
  for(int b=1; b<=bn; ++b) for(int u : blc[b]) lb[u] = b;
}

vector<int> bct[N];

void build_tree() {
  for(int u=1; u<=n; ++u) for(int v : adj[u]) if (num[u] > num[v]) {
    if (lb[u] == lb[v] or bh[lb[u]] == v) /* edge u-v belongs to block lb[u] */;
    else { /* edge u-v connects  articulation */;
      int x = (art[u] ? u + n : lb[u]), y = (art[v] ? v + n : lb[v]);
      bct[x].push_back(y), bct[y].push_back(x);
    }
  }
}
