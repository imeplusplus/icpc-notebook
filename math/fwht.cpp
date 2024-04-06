// Fast Walsh-Hadamard Transform - O(nlogn)
//
// Multiply two polynomials, but instead of x^a * x^b = x^(a+b)
// we have x^a * x^b = x^(a XOR b).
//
// WARNING: assert n is a power of two!
void fwht(ll* a, int n, bool inv) {
	for(int l=1; 2*l <= n; l<<=1) {
		for(int i=0; i < n; i+=2*l) {
			for(int j=0; j<l; j++) {
				ll u = a[i+j], v = a[i+l+j];

				a[i+j] = (u+v) % MOD; 
				a[i+l+j] = (u-v+MOD) % MOD;
				// % is kinda slow, you can use add() macro instead
				// #define add(x,y) (x+y >= MOD ? x+y-MOD : x+y)
			}
		}
	}

	if(inv) {
		for(int i=0; i<n; i++) {
			a[i] = a[i] / n;
		}
	}
}


/* FWHT AND
	Matrix : Inverse
	0 1      -1 1
	1 1       1 0
*/
void fwht_and(vi &a, bool inv) {
	vi ret = a;
	ll u, v;
	int tam = a.size() / 2;
	for(int len = 1; 2 * len <= tam; len <<= 1) {
		for(int i = 0; i < tam; i += 2 * len) {
			for(int j = 0; j < len; j++) {
				u = ret[i + j];
				v = ret[i + len + j];
				if(!inv) {
					ret[i + j] = v;
					ret[i + len + j] = u + v;
				}
				else {
					ret[i + j] = -u + v;
					ret[i + len + j] = u;
				}
			}
		}
	}
	a = ret;
}


/* FWHT OR
	Matrix : Inverse
	1 1      0  1
	1 0      1 -1
*/
void fft_or(vi &a, bool inv) {
	vi ret = a;
	ll u, v;
	int tam = a.size() / 2;
	for(int len = 1; 2 * len <= tam; len <<= 1) {
		for(int i = 0; i < tam; i += 2 * len) {
			for(int j = 0; j < len; j++) {
				u = ret[i + j];
				v = ret[i + len + j];
				if(!inv) {
					ret[i + j] = u + v;
					ret[i + len + j] = u;
				}
				else {
					ret[i + j] = v;
					ret[i + len + j] = u - v;
				}
			}
		}
	}
	a = ret;
}
