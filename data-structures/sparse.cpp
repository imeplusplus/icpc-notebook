const int N;
const int M; //log2(N)
int sparse[N][M];

void build() {
  for(int i = 0; i < n; i++)
    sparse[i][0] = v[i];

  for(int j = 1; j < M; j++)
    for(int i = 0; i < n; i++)
      sparse[i][j] = 
        i + (1 << j - 1) < n
        ? min(sparse[i][j - 1], sparse[i + (1 << j - 1)][j - 1]) 
        : sparse[i][j - 1];
}

int query(int a, int b){
  int pot = 32 - __builtin_clz(b - a) - 1;
  return min(sparse[a][pot], sparse[b - (1 << pot) + 1][pot]);
}
