int x[2*N];

int sat(int u) {
  x[u] = 1; x[u^1] = 0;
  for (int v : adj[u]) if (x[v] == -1)
    sat(v);
}

// main
n *= 2;
// find strongly connected components

int ok = 1;
for (int i = 0; i < n; i+=2) if (scc[i] == scc[i^1]) ok = 0;

cl(x, -1);
for (int i = 0; i < n; i+=2) if (x[i] == -1) {
  sat(scc[i] > scc[i^1] ? i : i^1);
}
