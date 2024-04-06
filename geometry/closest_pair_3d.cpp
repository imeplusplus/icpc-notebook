#include <bits/stdc++.h>

using namespace std;

#define st first
#define nd second

typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;

const ld EPS = 1e-9, PI = acos(-1.);
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const int N = 1e5+5;

typedef long long type;

struct point {
	type x, y, z;

	point() : x(0), y(0), z(0) {}
	point(type _x, type _y, type _z) : x(_x), y(_y) , z(_z) {}

	point operator -() { return point(-x, -y, -z); }
	point operator +(point p) { return point(x + p.x, y + p.y, z + p.z); }
	point operator -(point p) { return point(x - p.x, y - p.y, z - p.z); }

	point operator *(type k) { return point(x*k, y*k, z*k); }
	point operator /(type k) { return point(x/k, y/k, z/k); }

	bool operator ==(const point &p) const{ return x == p.x and y == p.y and z == p.z; }
	bool operator !=(const point &p) const{ return x != p.x  or y != p.y or z != p.z; }
	bool operator <(const point &p) const { return (z < p.z) or (z == p.z and y < p.y) or (z == p.z and y == p.y and x < p.x); }

	type abs2() { return x*x + y*y + z*z; }
	type dist2(point q) { return (*this - q).abs2(); }

};

ll cfloor(ll a, ll b) {
  ll c = abs(a);
  ll d = abs(b);
  if (a * b > 0) return c/d;
  return -(c + d - 1)/d;
}

ll min_dist = LINF;
pair<int, int> best_pair;
vector<point> pts;
int n;

//Warning: include variable id into the struct point
void upd_ans(const point & a, const point & b) {
	ll dist = (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z);
	if (dist < min_dist) {
		min_dist = dist;
		// best_pair = {a.id, b.id};
	}
}

void closest_pair(int l, int r) {
	if (r - l <= 3) {
		for (int i = l; i < r; ++i) {
			for (int j = i + 1; j < r; ++j) {
				upd_ans(pts[i], pts[j]);
			}
		}
		return;
	}

	int m = (l + r) >> 1;
	type midz = pts[m].z;
	closest_pair(l, m);
	closest_pair(m, r);

	//map opposite side
	map<pll, vector<int>> f;
	for(int i = m; i < r; i++){
		f[{cfloor(pts[i].x, min_dist), cfloor(pts[i].y, min_dist)}].push_back(i);
	}
	//find
	for(int i = l; i < m; i++){
		if((midz - pts[i].z) * (midz - pts[i].z) >= min_dist) continue;

		pll cur = {cfloor(pts[i].x, min_dist), cfloor(pts[i].y, min_dist)}; 
		for(int dx = -1; dx <= 1; dx++)
			for(int dy = -1; dy <= 1; dy++)
				for(auto p : f[{cur.st + dx, cur.nd + dy}])
					min_dist = min(min_dist, pts[i].dist2(pts[p]));
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	pts.resize(n);
	for(int i = 0; i < n; i++) cin >> pts[i].x >> pts[i].y >> pts[i].z;
	sort(pts.begin(), pts.end());
	closest_pair(0, n);
	cout << setprecision(15) << fixed << sqrt((ld)min_dist) << "\n";
	return 0;
}