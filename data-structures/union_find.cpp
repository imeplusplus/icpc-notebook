/**********************************************************************************
* DSU (DISJOINT SET UNION / UNION-FIND)                                           *
* Time complexity:  Unite - O(alpha n)                                            *
*                   Find - O(alpha n)                                             *
* Usage: find(node), unite(node1, node2), sz[find(node)]                          *
* Notation: par: vector of parents                                                *
*           sz:  vector of subsets sizes, i.e. size of the subset a node is in    *
**********************************************************************************/

int par[N], sz[N];

int find(int a) { return par[a] == a ? a : par[a] = find(par[a]); }

void unite(int a, int b) {
  if ((a = find(a)) == (b = find(b))) return;
  if (sz[a] < sz[b]) swap(a, b);
  par[b] = a; sz[a] += sz[b];
}

// in main
for (int i = 1; i <= n; i++) par[i] = i, sz[i] = 1;
