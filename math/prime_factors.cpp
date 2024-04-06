// Prime factors (up to 9*10^13. For greater see Pollard Rho)
vi factors;
int ind=0, pf = primes[0];
while (pf*pf <= n) {
	while (n%pf == 0) n /= pf, factors.pb(pf);
	pf = primes[++ind];
}
if (n != 1) factors.pb(n);
