// Sparse Table
// Sparse table O(nlogn)
int par[25][N];

// build
par[0][1] = 1;
for (int i = 0; (1<<i) < n; ++i)
  for (int j = 1; j <= n; ++j)
    par[i][j] = min(par[i-1][j], par[i-1][j+(1<<i)-1]);
