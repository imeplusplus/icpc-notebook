struct Sparse{
  int n, t[30][N];
  Sparse(int _n, int *v) {
    n = _n; f=_f;
    for(int i = 0; i < n; i++)
      t[0][i]=v[i];
    for(int i = 0; i < 29; i++)
      for(int j = 0; j+(1<<i)<n; j++)
        t[i+1][j]=min(t[i][j],t[i][j+(1<<i)]);
  }
  int qry(int l, int r) {
    int r=INF;
    for(int i=29;l!=r;i--)
      if(l+(1<<i)<=r)
        r=min(r,t[i][l]),l+=(1<<i);
    return r=min(r,t[0][r]);
  }
};
