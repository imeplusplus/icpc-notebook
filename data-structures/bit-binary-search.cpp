// --- Bit Binary Search in o(log(n)) ---
const int M = 20
const int N = 1 << M
  
int lower_bound(int val){
  int ans = 0, sum = 0;
  for(int i = M - 1; i >= 0; i--){
    int x = ans + (1 << i);
    if(sum + bit[x] < val) 
      ans = x, sum += bit[x];
  }

  return ans + 1;
}
