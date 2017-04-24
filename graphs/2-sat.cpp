// 2-SAT - O(V+E)
// For each variable, we create two nodes in the graph: u and !u
// If the variable has index i, the index of u and !u are: 2*i and 2*i+1
int ans[N];

void sat(int u) {
  ans[u] = 1; ans[u^1] = 0;
  for (int v : adj[u]) if (ans[v] == -1) sat(v);
}

// WARNING: EVERY PROPOSITION MUST BE ADDED WITH IT'S CONTRAPOSITION!
// u -> v <=> !v -> !u

bool sat() {
  // Use Kosaraju to get SCC in topological order. We assume that:
  // If node u is ancestor of node v, then scc[u] < scc[v].

  for (int i = 0; i < 2*n; i+=2)
    if (scc[i] == scc[i^1]) return 0;

  memset(ans, -1, sizeof ans);
  for (int i = 0; i < 2*n; i+=2) if (ans[i] == -1) {
    sat(scc[i] > scc[i^1] ? i : i^1);
  }
}
