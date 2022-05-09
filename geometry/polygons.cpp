#include "basics.cpp"
#include "lines.cpp"

//Graham scan NOT TESTED ENOUGH, not safe, prefer monotone chain!
point origin;

int above(point p){
    if(p.y == origin.y) return p.x > origin.x;
    return p.y > origin.y;
}

bool cmp(point p, point q){
    int tmp = above(q) - above(p);
    if(tmp) return tmp > 0;
    return p.dir(origin,q) > 0;
    //Be Careful: p.dir(origin,q) == 0
}

// Graham Scan O(nlog(n))
vector<point> graham_hull(vector<point> pts) {
    vector<point> ch(pts.size());
    point mn = pts[0];

    for(point p : pts) if (p.y < mn.y or (p.y == mn.y and p.x < mn.x)) mn = p;

    origin = mn;
    sort(pts.begin(), pts.end(), cmp);

    int n = 0;

    // IF: Convex hull without collinear points
    // for(point p : pts) {
    //     while (n > 1 and ch[n-1].dir(ch[n-2], p) < 1) n--;
    //     ch[n++] = p;
    // }

    //ELSE IF: Convex hull with collinear points
    for(point p : pts) {
    while (n > 1 and ch[n-1].dir(ch[n-2], p) < 0) n--;
    ch[n++] = p;
    }

    /*this part not safe
    for(int i=pts.size()-1; i >=1; --i)
    if (n > 1 and pts[i] != ch[n-1] and !pts[i].dir(pts[0], ch[n-1]))
        ch[n++] = pts[i];*/
    // END IF

    ch.resize(n);
    return ch;
}

//Monotone chain O(nlog(n))
#define REMOVE_REDUNDANT
#ifdef REMOVE_REDUNDANT
bool between(const point &a, const point &b, const point &c) {
    return (fabs(area_2(a,b,c)) < EPS && (a.x-b.x)*(c.x-b.x) <= 0 && (a.y-b.y)*(c.y-b.y) <= 0);
}
#endif

//new change: <= 0 / >= 0 became < 0 / > 0 (yet to be tested)

void monotone_hull(vector<point> &pts) {
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    vector<point> up, dn;
    for (int i = 0; i < pts.size(); i++) {
        while (up.size() > 1 && area_2(up[up.size()-2], up.back(), pts[i]) > 0) up.pop_back();
        while (dn.size() > 1 && area_2(dn[dn.size()-2], dn.back(), pts[i]) < 0) dn.pop_back();
        up.push_back(pts[i]);
        dn.push_back(pts[i]);
    }
    pts = dn;
    for (int i = (int) up.size() - 2; i >= 1; i--) pts.push_back(up[i]);

    #ifdef REMOVE_REDUNDANT
    if (pts.size() <= 2) return;
    dn.clear();
    dn.push_back(pts[0]);
    dn.push_back(pts[1]);
    for (int i = 2; i < pts.size(); i++) {
        if (between(dn[dn.size()-2], dn[dn.size()-1], pts[i])) dn.pop_back();
        dn.push_back(pts[i]);
    }
    if (dn.size() >= 3 && between(dn.back(), dn[0], dn[1])) {
        dn[0] = dn.back();
        dn.pop_back();
    }
    pts = dn;
    #endif
}

//avoid using long double for comparisons, change type and remove division by 2
ld compute_signed_area(const vector<point> &p) {
    ld area = 0;
    for(int i = 0; i < p.size(); i++) {
        int j = (i+1) % p.size();
        area += p[i].x*p[j].y - p[j].x*p[i].y;
    }
    return area / 2.0;
}

ld compute_area(const vector<point> &p) {
    return fabs(compute_signed_area(p));
}

ld compute_perimeter(vector<point> &p) {
    ld per = 0;
    for(int i = 0; i < p.size(); i++) {
        int j = (i+1) % p.size();
        per += p[i].dist(p[j]);
    }
    return per;
}

//not tested
// TODO: test this code. This code has not been tested, please do it before proper use.
// http://codeforces.com/problemset/problem/975/E is a good problem for testing.
point compute_centroid(vector<point> &p) {
    point c(0,0);
    ld scale = 6.0 * compute_signed_area(p);
    for (int i = 0; i < p.size(); i++){
        int j = (i+1) % p.size();
        c = c + (p[i]+p[j])*(p[i].x*p[j].y - p[j].x*p[i].y);
    }
    return c / scale;

}

// TODO: test this code. This code has not been tested, please do it before proper use.
// http://codeforces.com/problemset/problem/975/E is a good problem for testing.
point centroid(vector<point> &v) {
  int n = v.size();
  type da = 0;
  point m, c;

  for(point p : v) m = m + p;
  m = m / n;

  for(int i=0; i<n; ++i) {
    point p = v[i] - m, q = v[(i+1)%n] - m;
    type x = p % q;
    c = c + (p + q) * x;
    da += x;
  }

  return c / (3 * da);
}

//O(n^2)
bool is_simple(const vector<point> &p) {
    for (int i = 0; i < p.size(); i++) {
        for (int k = i+1; k < p.size(); k++) {
            int j = (i+1) % p.size();
            int l = (k+1) % p.size();
            if (i == l || j == k) continue;
            if (segment_segment_intersect(p[i], p[j], p[k], p[l])) 
                return false;
        }
    }
    return true;
}

bool point_in_triangle(point a, point b, point c, point cur){
    ll s1 = abs(cross(b - a, c - a));
    ll s2 = abs(cross(a - cur, b - cur)) + abs(cross(b - cur, c - cur)) + abs(cross(c - cur, a - cur));
    return s1 == s2;
}

void sort_lex_hull(vector<point> &hull){
    int n = hull.size();

    //Sort hull by x
    int pos = 0;
    for(int i = 1; i < n; i++) if(hull[i] <  hull[pos]) pos = i;
    rotate(hull.begin(), hull.begin() + pos, hull.end());
}

//determine if point is inside or on the boundary of a polygon (O(logn))
bool point_in_convex_polygon(vector<point> &hull, point cur){
    int n = hull.size();
    //Corner cases: point outside most left and most right wedges
    if(cur.dir(hull[0], hull[1]) != 0 && cur.dir(hull[0], hull[1]) != hull[n - 1].dir(hull[0], hull[1]))
        return false;
    if(cur.dir(hull[0], hull[n - 1]) != 0 && cur.dir(hull[0], hull[n - 1]) != hull[1].dir(hull[0], hull[n - 1]))
        return false;

    //Binary search to find which wedges it is between
    int l = 1, r = n - 1;
    while(r - l > 1){
        int mid = (l + r)/2;
        if(cur.dir(hull[0], hull[mid]) <= 0)l = mid;
        else r = mid;
    }
    return point_in_triangle(hull[l], hull[l + 1], hull[0], cur);
}

// determine if point is on the boundary of a polygon (O(N))
bool point_on_polygon(vector<point> &p, point q) {
for (int i = 0; i < p.size(); i++)
    if (q.dist2(project_point_segment(p[i], p[(i+1)%p.size()], q)) < EPS) return true;
    return false;
}

//Shamos - Hoey for test polygon simple in O(nlog(n))
inline bool adj(int a, int b, int n) {return (b == (a + 1)%n or a == (b + 1)%n);}

struct edge{
    point ini, fim;
    edge(point ini = point(0,0), point fim = point(0,0)) : ini(ini), fim(fim) {}
};

//< here means the edge on the top will be at the begin
bool operator < (const edge& a, const edge& b) {
    if (a.ini == b.ini) return direction(a.ini, a.fim, b.fim) < 0;
    if (a.ini.x < b.ini.x) return direction(a.ini, a.fim, b.ini) < 0;
    return direction(a.ini, b.fim, b.ini) < 0;
}

bool is_simple_polygon(const vector<point> &pts){
    vector <pair<point, pii>> eve;
    vector <pair<edge, int>> edgs;
    set <pair<edge, int>> sweep;
    int n = (int)pts.size();
    for(int i = 0; i < n; i++){
        point l = min(pts[i], pts[(i + 1)%n]);
        point r = max(pts[i], pts[(i + 1)%n]);
        eve.pb({l, {0, i}});
        eve.pb({r, {1, i}});
        edgs.pb(make_pair(edge(l, r), i));
    }
    sort(eve.begin(), eve.end());
    for(auto e : eve){
        if(!e.nd.st){
            auto cur = sweep.lower_bound(edgs[e.nd.nd]);
            pair<edge, int> above, below;
            if(cur != sweep.end()){
                below = *cur;
                if(!adj(below.nd, e.nd.nd, n) and segment_segment_intersect(pts[below.nd], pts[(below.nd + 1)%n], pts[e.nd.nd], pts[(e.nd.nd + 1)%n]))
                    return false;
            }
            if(cur != sweep.begin()){
                above = *(--cur);
                if(!adj(above.nd, e.nd.nd, n) and segment_segment_intersect(pts[above.nd], pts[(above.nd + 1)%n], pts[e.nd.nd], pts[(e.nd.nd + 1)%n]))
                    return false;
            }
            sweep.insert(edgs[e.nd.nd]);
        }
        else{
            auto below = sweep.upper_bound(edgs[e.nd.nd]);
            auto cur = below, above = --cur;
            if(below != sweep.end() and above != sweep.begin()){
                --above;
                if(!adj(below->nd, above->nd, n) and segment_segment_intersect(pts[below->nd], pts[(below->nd + 1)%n], pts[above->nd], pts[(above->nd + 1)%n]))
                    return false;
            }
            sweep.erase(cur);
        }
    }
    return true;
}

//code copied from https://github.com/tfg50/Competitive-Programming/blob/master/Biblioteca/Math/2D%20Geometry/ConvexHull.cpp
int maximize_scalar_product(vector<point> &hull, point vec) {
	// this code assumes that there are no 3 colinear points
	int ans = 0;
	int n = hull.size();
	if(n < 20) {
		for(int i = 0; i < n; i++) {
			if(hull[i] * vec > hull[ans] * vec) {
				ans = i;
			}
		}
	} else {
		if(hull[1] * vec > hull[ans] * vec) {
			ans = 1;
		}
		for(int rep = 0; rep < 2; rep++) {
			int l = 2, r = n - 1;
			while(l != r) {
				int mid = (l + r + 1) / 2;
				bool flag = hull[mid] * vec >= hull[mid-1] * vec;
				if(rep == 0) { flag = flag && hull[mid] * vec >= hull[0] * vec; }
				else { flag = flag || hull[mid-1] * vec < hull[0] * vec; }
				if(flag) {
					l = mid;
				} else {
					r = mid - 1;
				}
			}
			if(hull[ans] * vec < hull[l] * vec) {
				ans = l;
			}
		}
	}
	return ans;
}

//find tangents related to a point outside the polygon, essentially the same for maximizing scalar product
int tangent(vector<point> &hull, point vec, int dir_flag) {
	// this code assumes that there are no 3 colinear points
    // dir_flag = -1 for right tangent
    // dir_flag =  1 for left taangent
	int ans = 0;
	int n = hull.size();
	if(n < 20) {
		for(int i = 0; i < n; i++) {
			if(hull[ans].dir(vec, hull[i]) == dir_flag) {
				ans = i;
			}
		}
	} else {
		if(hull[ans].dir(vec, hull[1]) == dir_flag) {
			ans = 1;
		}
		for(int rep = 0; rep < 2; rep++) {
			int l = 2, r = n - 1;
			while(l != r) {
				int mid = (l + r + 1) / 2;
				bool flag = hull[mid - 1].dir(vec, hull[mid]) == dir_flag;
				if(rep == 0) { flag = flag && (hull[0].dir(vec, hull[mid]) == dir_flag); }
				else { flag = flag || (hull[0].dir(vec, hull[mid - 1]) != dir_flag); }
				if(flag) {
					l = mid;
				} else {
					r = mid - 1;
				}
			}
			if(hull[ans].dir(vec, hull[l]) == dir_flag) {
				ans = l;
			}
		}
	}
	return ans;
}