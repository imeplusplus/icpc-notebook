// Fenwick Tree / Binary Indexed Tree
int bit[N];

void add(int p, int v) {
  for (p+=2; p<N; p+=p&-p) bit[p] += v;
}

int query(int p) {
  int r = 0;
  for (p+=2; p; p-=p&-p) r += bit[p];
  return r;
}

// --- Binary Search in o(log(n)) ---
const int M = 20
const int N = 1 << M
  
int binary_search(int val){ //ans => first greater than x
  int ans = 0, sum = 0;
  for(int i = M - 1; i >= 0; i--){
    int x = ans + (1 << i);
    if(sum + bit[x] < val) 
      ans = x, sum += bit[x];
  }

  return ans + 1;
}
