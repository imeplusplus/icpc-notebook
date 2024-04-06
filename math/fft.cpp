// Fast Fourier Transform - O(nlogn)

/*
// Use struct instead. Performance will be way better!
typedef complex<ld> T;
T a[N], b[N];
*/

struct T {
	ld x, y;
	T() : x(0), y(0) {}
	T(ld a, ld b=0) : x(a), y(b) {}

	T operator/=(ld k) { x/=k; y/=k; return (*this); }
	T operator*(T a) const { return T(x*a.x - y*a.y, x*a.y + y*a.x); }
	T operator+(T a) const { return T(x+a.x, y+a.y); }
	T operator-(T a) const { return T(x-a.x, y-a.y); }
} a[N], b[N];

// a: vector containing polynomial
// n: power of two greater or equal product size
/*
// Use iterative version!
void fft_recursive(T* a, int n, int s) {
	if (n == 1) return;
	T tmp[n];
	for (int i = 0; i < n/2; ++i)
		tmp[i] = a[2*i], tmp[i+n/2] = a[2*i+1];

	fft_recursive(&tmp[0], n/2, s);
	fft_recursive(&tmp[n/2], n/2, s);

	T wn = T(cos(s*2*PI/n), sin(s*2*PI/n)), w(1,0);
	for (int i = 0; i < n/2; i++, w=w*wn)
		a[i] = tmp[i] + w*tmp[i+n/2],
		a[i+n/2] = tmp[i] - w*tmp[i+n/2];
}
*/

void fft(T* a, int n, int s) {
	for (int i=0, j=0; i<n; i++) {
		if (i>j) swap(a[i], a[j]);
		for (int l=n/2; (j^=l) < l; l>>=1);
	}

	for(int i = 1; (1<<i) <= n; i++){
		int M = 1 << i;
		int K = M >> 1;
		T wn = T(cos(s*2*PI/M), sin(s*2*PI/M));
		for(int j = 0; j < n; j += M) {
			T w = T(1, 0);
			for(int l = j; l < K + j; ++l){
				T t = w*a[l + K];
				a[l + K] = a[l]-t;
				a[l] = a[l] + t;
				w = wn*w;
			}
		}
	}
}

// assert n is a power of two greater of equal product size
// n = na + nb; while (n&(n-1)) n++;
void multiply(T* a, T* b, int n) {
	fft(a,n,1);
	fft(b,n,1);
	for (int i = 0; i < n; i++) a[i] = a[i]*b[i];
	fft(a,n,-1);
	for (int i = 0; i < n; i++) a[i] /= n;
}

// Convert to integers after multiplying:
// (int)(a[i].x + 0.5);
