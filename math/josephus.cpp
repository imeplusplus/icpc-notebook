// UFMG
/* Josephus Problem - It returns the position to be, in order to not die. O(n)*/
/* With k=2, for instance, the game begins with 2 being killed and then n+2, n+4, ... */
ll josephus(ll n, ll k) {
	if(n==1) return 1;
	else return (josephus(n-1, k)+k-1)%n+1;
}

/* Another Way to compute the last position to be killed - O(d * log n) */
ll josephus(ll n, ll d) {
	ll K = 1;
	while (K <= (d - 1)*n) K = (d * K + d - 2) / (d - 1);
	return d * n + 1 - K;
}
