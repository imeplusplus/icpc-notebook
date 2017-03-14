const int mod = 479*(1<<21)+1;
const int root = 3;
const int root_1 = 334845270;
const int root_pw = 1<<21;

const int mod = 7*(1<<20)+1;
const int root = 5;
const int root_1 = 4404020;
const int root_pw = 1<<20;

// a: vector containing polynomial
// n: power of two greater or equal product size
void ntt(ll* a, int n, bool inv) {
  for (int i=1, j=0; i<n; ++i) {
    int bit = n >> 1;
    for (; j>=bit; bit>>=1)
      j -= bit;
    j += bit;
    if (i < j)
      swap (a[i], a[j]);
  }

  for (int k=2; k<=n; k<<=1) {
    ll len = inv ? root_1 : root;
    for (int i=k; i<root_pw; i<<=1) len *= len, len %= mod;;

    for (int i=0; i<n; i+=k) {
      int w = 1;
      for (int j=0; j<k/2; ++j) {
        int u = a[i+j],  v = int (a[i+j+k/2] * 1ll * w % mod);
        a[i+j] = (u+v)%mod;
        a[i+j+k/2] = (u-v+mod)%mod;
        w = 1ll*w*len % mod;
      }
    }
  }
  if (inv) {
    int nrev = exp(n, mod-2, mod);
    for (int i=0; i<n; ++i)
      a[i] = 1ll*a[i]*nrev % mod;
  }
}
