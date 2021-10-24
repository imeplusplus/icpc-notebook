// Multiplicative Inverse over MOD for all 1..N - 1 < MOD in O(N)
// If all 1..MOD - 1 needed, use N = MOD
ll inv[N];
inv[1] = 1;
for (int i = 2; i < N; ++i)
  inv[i] = (MOD - (MOD / i) * inv[MOD % i] % MOD) % MOD;

// Recurrence using matriz
// h[i + 2] = a1 * h[i + 1] + a0 * h[i]
// [h[i] h[i-1]] = [h[1] h[0]] * [a1 1] ^ (i - 1)
//                               [a0 0] 

// Fibonacci in O(log(N))
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
// |Classes| = 1 / |G| * sum(K ^ C(g)) for each g in G
// G = Different permutations possible
// C(g) = Number of cycles on the permutation g
// K = Number of states for each element
//
// Different ways to paint a necklace with N beads and K colors:
// G = {(1, 2, ... N), (2, 3, ... N, 1), ... (N, 1, ... N - 1)}
// gi = (i, i + 1, ... i + N), (taking mod N to get it right) i = 1 ... N
// i -> 2i -> 3i ..., Cycles in gi all have size n / gcd(i, n), so C(gi) = gcd(i, n)
// Ans = 1 / N * sum(K ^ gcd(i, n)), i = 1 ... N
// (For the brave, you can get to Ans = 1 / N * sum(euler_phi(N / d) * K ^ d), d | N)

// Mobius Inversion
// How many pairs do we have with gcd(i, j), i, j = 1 .. N?
// sum(k->N) k * sum(i->N) sum(j->N) [gcd(i, j) == k], i = a * k, j = b * k
// = sum(k->N) k * sum(a->N/k) sum(b->N/k) [gcd(a, b) == 1]
// = sum(k->N) k * sum(a->N/k) sum(b->N/k) sum(d->N/k) [d | a] * [d | b] * mi(d)
// = sum(k->N) k * sum(d->N/k) mi(d) * floor(N / kd)², l = kd, l <= N, k | l, d = l / k
// k|l -> k divides l
// = sum(l->N) floor(N / l)² * sum(k|l) k * mi(l / k)
// If f(n) = sum(x|n)(g(x) * h(x)) with g(x) and h(x) multiplicative, than f(n) is multiplicative
// Hence, g(l) = sum(k|l) k * mi(l / k) is multiplicative
// = sum(l->N) floor(N / l)² * g(l)
