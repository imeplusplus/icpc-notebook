// Kruskal - MST O(ElogE)
vector<piii> edges;
// + Union-find

sort(edges.begin(), edges.end());
int cost = 0;
for (auto e : edges)
  if (find(e.nd.st) != find(e.nd.nd))
    unite(e.nd.st, e.nd.nd), cost += e.st;
