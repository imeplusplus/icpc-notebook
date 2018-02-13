// Multiply two polynomials, but instead of x^a * x^b = x^(a+b)
// we have x^a * x^b = x^(a XOR b).
//
// Also you can look at it as a multivariable cyclic convolution
void fwht(ll* a, int n, bool inv) {
  for(int l=1; 2*l <= n; l<<=1) {
    for(int i=0; i < n; i+=2*l) {
      for(int j=0; j<l; j++) {
        ll u = a[i+j], v = a[i+l+j];

        a[i+j] = (u+v) % MOD; 
        a[i+l+j] = (u-v+MOD) % MOD;
        // % is kinda slow, you can use add() macro instead
        // #define add(x,y) (x+y >= MOD : x+y-MOD : x+y)
      }
    }
  }

  if(inv) {
    for(int i=0; i<n; i++) {
      a[i] = a[i] / n;
    }
  }
}

// assert n is a power of two!
