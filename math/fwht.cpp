template<const char ch, class T>
std::vector<T> FWHT(std::vector<T> a, const bool inv = false) {
	int n = (int) a.size();
	for(int len = 1; len < n; len += len) {
		for(int i = 0; i < n; i += 2 * len) {
			for(int j = 0; j < len; j++) {
				auto u = a[i + j], v = a[i + j + len];
				if(ch == '^') {
					a[i + j] = u + v;
					a[i + j + len] = u - v;
				}
				if(ch == '|') {
					if(!inv) {
						a[i + j + len] += a[i + j];
					} else {
						a[i + j + len] -= a[i + j];
					}
				}
				if(ch == '&') {
					if(!inv) {
						a[i + j] += a[i + j + len];
					} else {
						a[i + j] -= a[i + j + len];
					}
				}
			}
		}
	}
	if(ch == '^' && inv) {
		for(int i = 0; i < n; i++) {
			a[i] = a[i] / n;
		}
	}
	return a;
}