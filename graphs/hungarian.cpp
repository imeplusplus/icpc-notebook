// Hungarian - O(m*n^2)
// Assignment Problem

int n, m;
int pu[N], pv[N], cost[N][M];
int pairV[N], way[M], minv[M], used[M];

void hungarian() {
  for(int i = 1, j0 = 0; i <= n; i++) {
    pairV[0] = i;
    memset(minv, 63, sizeof minv);
    memset(used, 0, sizeof used);
    do {
      used[j0] = 1;
      int i0 = pairV[j0], delta = INF, j1;
      for(int j = 1; j <= m; j++) {
        if(used[j]) continue;
        int cur = cost[i0][j] - pu[i0] - pv[j];
        if(cur < minv[j]) minv[j] = cur, way[j] = j0;
        if(minv[j] < delta) delta = minv[j], j1 = j;
      }
      
      for(int j = 0; j <= m; j++) {
        if(used[j]) pu[pairV[j]] += delta, pv[j] -= delta;
        else minv[j] -= delta;
      }
      j0 = j1;
    } while(pairV[j0]);
    
    do {
      int j1 = way[j0];
      pairV[j0] = pairV[j1];
      j0 = j1;
    } while(j0);
  }
}

// in main
// for(int j = 1; j <= m; j++) 
//  if(pairV[j]) ans += cost[pairV[j]][j];
// 
