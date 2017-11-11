#include <bits/stdc++.h>
using namespace std;

const int N = 2e6+1, K = 26;
int sl[N], len[N], sz, last;
int cnt[N];
map<int, int> g[N];

void add(int c) {
  int u = ++sz;
  len[u] = len[last] + 1;
  cnt[u] = 1;

  int p = last;
  while(p and !g[p][c])
    g[p][c] = u, p = sl[p];

  if (!p) sl[u] = 1;
  else {
    int q = g[p][c];
    if (len[p] + 1 == len[q]) sl[u] = q;
    else {
      int r = ++sz;
      len[r] = len[p] + 1;
      sl[r] = sl[q];
      g[r] = g[q];
      while(p) g[p][c] = r, p = sl[p];
      sl[q] = sl[u] = r;
    }
  }

  last = u;
}

vector<int> t[N];

void dfs(int u) {
  for(int v : t[u])
    dfs(v), cnt[u] += cnt[v];
}

void build_tree() {
  for(int i=1; i<=sz; ++i)
    t[sl[i]].push_back(i);

  dfs(1);
}

