#include <bits/stdc++.h>

using lint = int64_t;

constexpr int MOD = int(1e9) + 7;
constexpr int INF = 0x3f3f3f3f;
constexpr int NINF = 0xcfcfcfcf;
constexpr lint LINF = 0x3f3f3f3f3f3f3f3f;

#define endl '\n'

const long double PI = acosl(-1.0);

int cmp_double(double a, double b = 0, double eps = 1e-9) {
	return a + eps > b ? b + eps > a ? 0 : 1 : -1;
}

using namespace std;

#define P 1000000007
#define N 330000

int n, m;
vector<int> go[N], lk[N];
int w[N], deg[N], pos[N], id[N];

bool circle3() {
	int ans = 0;
	for(int i = 1; i <= n; i++) w[i] = 0;
	for(int x = 1; x <= n; x++)  {
		for(int y : lk[x]) w[y] = 1;
		for(int y : lk[x]) for(int z:lk[y]) if(w[z]) {
			ans=(ans+go[x].size()+go[y].size()+go[z].size() - 6);
			if(ans) return true;
		}
		for(int y:lk[x]) w[y] = 0;
	}
	return false;
}

bool circle4() {
	for(int i = 1; i <= n; i++) w[i] = 0;
	int ans = 0;
	for(int x = 1; x <= n; x++) {
		for(int y:go[x]) for(int z:lk[y]) if(pos[z] > pos[x]) {
			ans = (ans+w[z]);
			w[z]++;
			if(ans) return true;
		}
		for(int y:go[x]) for(int z : lk[y]) w[z] = 0;
	}
	return false;
}

inline bool cmp(const int &x, const int &y) {
	return deg[x] < deg[y];
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false); 
	cin >> n >> m;

	int x, y;
	for(int i = 0; i < n; i++) {
		cin >> x >> y;
	}

	for(int i = 1; i <= n; i++) {
		deg[i] = 0, go[i].clear(), lk[i].clear();
	} 
	while (m--){
		int a, b;
		cin >> a >> b;
		deg[a]++, deg[b]++;
		go[a].push_back(b);
		go[b].push_back(a);
	}

	for(int i = 1; i <= n; i++) id[i]= i;
	sort(id+1, id+1+n, cmp);
	for(int i = 1; i<= n; i++) pos[id[i]]=i;
	for(int x = 1; x<= n; x++) {
		for(int y:go[x]) {
			if(pos[y]>pos[x]) lk[x].push_back(y);
		}
	};

	if(circle3()) {
		cout << "3" << endl;
		return 0;
	};

	if(circle4()) {
		cout << "4" << endl;
		return 0;
	};

	cout << "5" << endl;
	return 0;
}