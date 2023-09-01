//TFG50 Voronoi - source code: https://github.com/tfg50/Competitive-Programming/tree/master/Biblioteca/Math/2D%20Geometry
#include<bits/stdc++.h>
#include <chrono>
#include <random>

std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());

struct PT {
	typedef long long T;
	T x, y;
	PT(T _x = 0, T _y = 0) : x(_x), y(_y){}
	PT operator +(const PT &p) const { return PT(x+p.x,y+p.y); }
	PT operator -(const PT &p) const { return PT(x-p.x,y-p.y); }
	PT operator *(T c)         const { return PT(x*c,y*c);     }
	//PT operator /(double c)    const { return PT(x/c,y/c);     }
	T operator *(const PT &p)  const { return x*p.x+y*p.y;     }
	T operator %(const PT &p)  const { return x*p.y-y*p.x;     }
	//double operator !()        const { return sqrt(x*x+y*y);   }
	//double operator ^(const PT &p) const { return atan2(*this%p, *this*p);}
	bool operator < (const PT &p) const { return x != p.x ? x < p.x : y < p.y; }
	bool operator == (const PT &p)const { return x == p.x && y == p.y; }

	friend std::ostream& operator << (std::ostream &os, const PT &p) {
		return os << p.x << ' ' << p.y;
	}
	friend std::istream& operator >> (std::istream &is, PT &p) {
		return is >> p.x >> p.y;
	}
};

struct Segment {
	typedef long double T;
	PT p1, p2;
	T a, b, c;

	Segment() {}

	Segment(PT st, PT en) {
		p1 = st, p2 = en;
		a = -(st.y - en.y);
		b = st.x - en.x;
		c = a * en.x + b * en.y;
	}

	T plug(T x, T y) {
		// plug >= 0 is to the right
		return a * x + b * y - c;
	}

	T plug(PT p) {
		return plug(p.x, p.y);
	}

	bool inLine(PT p) { return (p - p1) % (p2 - p1) == 0; }
	bool inSegment(PT p) {
		return inLine(p) && (p1 - p2) * (p - p2) >= 0 && (p2 - p1) * (p - p1) >= 0;
	}

	PT lineIntersection(Segment s) {
		long double A = a, B = b, C = c;
		long double D = s.a, E = s.b, F = s.c;
		long double x = (long double) C * E - (long double) B * F;
		long double y = (long double) A * F - (long double) C * D;
		long double tmp = (long double) A * E - (long double) B * D;
		x /= tmp;
		y /= tmp;
		return PT(x, y);
	}
	
	bool polygonIntersection(const std::vector<PT> &poly) {
		long double l = -1e18, r = 1e18;
		for(auto p : poly) {
			long double z = plug(p);
			l = std::max(l, z);
			r = std::min(r, z);
		}
		return l - r > eps;
	}
};

std::vector<PT> cutPolygon(std::vector<PT> poly, Segment seg) {
	int n = (int) poly.size();
	std::vector<PT> ans;
	for(int i = 0; i < n; i++) {
		double z = seg.plug(poly[i]);
		if(z > -eps) {
			ans.push_back(poly[i]);
		}
		double z2 = seg.plug(poly[(i + 1) % n]);
		if((z > eps && z2 < -eps) || (z < -eps && z2 > eps)) {
			ans.push_back(seg.lineIntersection(Segment(poly[i], poly[(i + 1) % n])));
		}
	}
	return ans;
}

Segment getBisector(PT a, PT b) {
	Segment ans(a, b);
	std::swap(ans.a, ans.b);
	ans.b *= -1;
	ans.c = ans.a * (a.x + b.x) * 0.5 + ans.b * (a.y + b.y) * 0.5;
	return ans;
}




// BE CAREFUL!
// the first point may be any point
// O(N^3)
std::vector<PT> getCell(std::vector<PT> pts, int i) {
	std::vector<PT> ans;
	ans.emplace_back(0, 0);
	ans.emplace_back(1e6, 0);
	ans.emplace_back(1e6, 1e6);
	ans.emplace_back(0, 1e6);
	for(int j = 0; j < (int) pts.size(); j++) {
		if(j != i) {
			ans = cutPolygon(ans, getBisector(pts[i], pts[j]));
		}
	}
	return ans;
}

// O(N^2) expected time
std::vector<std::vector<PT>> getVoronoi(std::vector<PT> pts) {
	// assert(pts.size() > 0);
	int n = (int) pts.size();
	std::vector<int> p(n, 0);
	for(int i = 0; i < n; i++) {
		p[i] = i;
	}
	shuffle(p.begin(), p.end(), rng);
	std::vector<std::vector<PT>> ans(n);
	ans[0].emplace_back(0, 0);
	ans[0].emplace_back(w, 0);
	ans[0].emplace_back(w, h);
	ans[0].emplace_back(0, h);
	for(int i = 1; i < n; i++) {
		ans[i] = ans[0];
	}
	for(auto i : p) {
		for(auto j : p) {
			if(j == i) break;
			auto bi = getBisector(pts[j], pts[i]);
			if(!bi.polygonIntersection(ans[j])) continue;
			ans[j] = cutPolygon(ans[j], getBisector(pts[j], pts[i]));
			ans[i] = cutPolygon(ans[i], getBisector(pts[i], pts[j]));
		}
	}
	return ans;
}













