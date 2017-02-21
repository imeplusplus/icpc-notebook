typedef complex<ld> T;
typedef vector<T> VT;
T tmp[N];

void fft(T* a, int n, bool inv) {
  if (n == 1) return;
  for (int i = 0; i < n/2; ++i)
    tmp[i] = a[2*i], tmp[i+n/2] = a[2*i+1];

  fft(&tmp[0], n/2, inv);
  fft(&tmp[n/2], n/2, inv);

  T wn = exp(T(0, (inv?-2:2)*M_PI/n)), w(1);
  for (int i = 0; i < n/2; ++i, w*=wn)
    a[i] = tmp[i] + w*tmp[i+n/2],
    a[i+n/2] = tmp[i] - w*tmp[i+n/2];
}

void multiply(VT& a, VT b) {
  int n = a.size() + b.size();
  while (n&(n-1)) ++n;
  a.resize(n); b.resize(n);

  fft(&a[0],n,0);
  fft(&b[0],n,0);
  for (int i = 0; i < n; ++i) a[i] *= b[i];

  fft(&a[0],n,1);
  for (int i = 0; i < n; ++i) a[i] /= n;
}
