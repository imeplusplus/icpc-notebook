// 1 if n == 1
// 0 if exists x | n%(x^2) == 0
// else (-1)^k, k = #(p) | p is prime and n%p == 0

//Calculate Mobius for all integers using sieve
//O(n*log(log(n)))
void mobius() {
	for(int i = 1; i < N; i++) mob[i] = 1;

	for(ll i = 2; i < N; i++) if(!sieve[i]){
		for(ll j = i; j < N; j += i) sieve[j] = i, mob[j] *= -1;
		for(ll j = i*i; j < N; j += i*i) mob[j] = 0;
	}
}

/*
//Calculate Mobius for 1 integer
//O(sqrt(n))
int mobius(int n){
	if(n == 1) return 1;
	int p = 0;
	for(int i = 2; i*i <= n; i++)
		if(n%i == 0){
			n /= i;
			p++;
			if(n%i == 0) return 0;
		}
	if(n > 1) p++;
	return p&1 ? -1 : 1;
}
*/
