struct lichao {
	struct line {
		long long m, b;
		long long operator()(long long x) const {
			return m * x + b;
		}
		bool cmp(const line &a, long long x) {
			return (*this)(x) < a(x);
		}
	};
	vector<line> seg;
	vector<int> L, R;
	inline void push() {
			seg.push_back({0, -linf});
			L.push_back(-1);
			R.push_back(-1);
	}
	lichao() {
			push();
	}
	void add(line a, int p = 0, long long l = -MAX, long long r = MAX) {
		long long mid = (l + r) >> 1;
		if(seg[p].cmp(a, mid)) {
			swap(seg[p], a);
		}
		if(a.b == -linf) {
			return;
		}
		if(seg[p].cmp(a, l) != seg[p].cmp(a, mid)) {
			if(L[p] == -1) {
				L[p] = seg.size();
				push();
			}
			add(a, L[p], l, mid - 1);
		} else if(seg[p].cmp(a, r) != seg[p].cmp(a, mid)) {
			if(R[p] == -1) {
				R[p] = seg.size();
				push();
			}
			add(a, R[p], mid + 1, r);
		}
	}
	long long query(long long x, int p = 0, long long l = -MAX, long long r = MAX) {
			if(p < 0) {
				return -linf;
			}
			long long mid = (l + r) >> 1, calc = seg[p](x);
			if(calc == -linf) {
				return calc;
			}
			if(x < mid) {
				return max(calc, query(x, L[p], l, mid - 1));
			} else {
				return max(calc, query(x, R[p], mid + 1, r));
			}
	}
};