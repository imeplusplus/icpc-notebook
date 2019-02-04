// 1 if n == 1
// 0 if exists x | n%x² == 0
// else (-1)^k, k = #(p) | p is prime and n%p == 0

int mobius(int n){
  if(n == 1) return 1;
  int p = 0;
  for(int i = 2; i*i <= n; i++)
    if(n%i == 0){
      n /= i;
      p++;
      if(n%i == 0) return 0;
    }
  return p&1 ? 1 : -1;
}
