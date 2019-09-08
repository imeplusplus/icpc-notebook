// Greatest Common Divisor & Lowest Common Multiple
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a/gcd(a, b)*b; }

// Multiply caring overflow
ll mulmod(ll a, ll b, ll m = MOD) {
  ll r=0;
  for (a %= m; b; b>>=1, a=(a*2)%m) if (b&1) r=(r+a)%m;
  return r;
}

// Another option for mulmod is using long double
ull mulmod(ull a, ull b, ull m = MOD) {
  ull q = (ld) a * (ld) b / (ld) m;
  ull r = a * b - q * m;
  return (r + m) % m;
}

// Fast exponential
ll fexp(ll a, ll b, ll m = MOD) {
  ll r=1;
  for (a %= m; b; b>>=1, a=(a*a)%m) if (b&1) r=(r*a)%m;
  return r;
}

// Multiplicative Inverse
ll inv[N];
inv[1] = 1;
for (int i = 2; i < MOD; ++i)
  inv[i] = (MOD - (MOD/i)*inv[MOD%i]%MOD)%MOD;

// Fibonacci
// Fn = Fn-1 + Fn-2
// F0 = 0 ; F1 = 1
f[0] = 0; f[1] = 1;
for (int i = 2; i <= n; i++) f[i] = f[i-1] + f[i-2];

// Recurrence using matriz
// h[i+2] = a1*h[i+1] + a0*h[i]
// [ h[i] h[i-1] ] = [ h[1] h[0] ] * [ a1 1 ] ^ (i - 1)
//                                   [ a0 0 ] 

// Fibonacci in logarithm time
// f(2*k) = f(k)*(2*f(k + 1) - f(k))
// f(2*k + 1) = f(k)^2 + f(k + 1)^2

// Catalan
// Cn = (2n)! / ((n+1)! * n!)
// 1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786, 208012, 742900, 2674440
cat[n] = (2*(2*n-1)/(n+1)) * cat[n-1]

// Stirling
// S(n, 1) = S(n, n) = 1
// S(n, k) = k*S(n-1, k) + S(n-1, k-1)

// Burnside's Lemma
// Counts the number of equivalence classes in a set.
// Let G be a group of operations acting on a set X. The number of equivalence classes given those operations |X/G| satisfies:
//
// |X/G| = 1/|G| * sum(I(g)) for each g in G
//
// Being I(g) the number of fixed points given the operation g.
