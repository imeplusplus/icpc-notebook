#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

typedef long double ld;
const double EPS = 1e-9;

bool ge(ld x, ld y) { return x + EPS > y; }
bool le(ld x, ld y) { return x - EPS < y; }
bool eq(ld x, ld y) { return ge(x, y) and le(x, y); }

struct point {
  ld x, y;

  point() : x(0), y(0) {}
  point(ld x, ld y) : x(x), y(y) {}

  point operator -() { return point(-x, -y); }
  point operator +(point p) { return point(x+p.x, y+p.y); }
  point operator -(point p) { return point(x-p.x, y-p.y); }

  point operator *(ld k) { return point(k*x, k*y); }
  point operator /(ld k) { return point(x/k, y/k); }

  ld operator *(point p) { return x*p.x + y*p.y; }
  ld operator %(point p) { return x*p.y - y*p.x; }

  // o is the origin, p is another point
  // dir == +1 => p is clockwise from this
  // dir ==  0 => p is colinear with this
  // dir == -1 => p is counterclockwise from this
  int dir(point o, point p) {
    ld x = (*this - o) % (p - o);
    return ge(x,0) - le(x,0);
  }

  bool on_seg(point p, point q) {
    if (this->dir(p, q)) return 0;
    return ge(x, min(p.x, q.x)) and le(x, max(p.x, q.x)) and
           ge(y, min(p.y, q.y)) and le(y, max(p.y, q.y));
  }

  ld abs() { return sqrt(x*x + y*y); }
  ld dist(point x) { return (*this - x).abs(); }

  point project(point y) { return y * ((*this * y) / (y * y)); }

  ld dist_line(point x, point y) {
    point t = *this-x;
    return dist(t.project(y-x) + x);
  }

  ld dist_seg(point x, point y) {
    return min(dist_line(x, y), min(dist(x), dist(y)));
  }

  point rotate(ld a) {
    return point(cos(a)*x-sin(a)*y, sin(a)*x+cos(a)*y);
  }

  point rotate(point p) { // rotate around the argument from vector p
    ld hyp = (p.x+p.y) * (p.x+p.y);
    ld c = p.x / hyp;
    ld s = p.y / hyp;
    return point(c*x-s*y, s*x+c*y);
  }
};


int direction(point o, point p, point q) { return p.dir(o, q); }

bool segments_intersect(point p, point q, point a, point b) {
  int d1, d2, d3, d4;
  d1 = direction(p, q, a);
  d2 = direction(p, q, b);
  d3 = direction(a, b, p);
  d4 = direction(a, b, q);
  if (d1*d2 < 0 and d3*d4 < 0) return 1;
  return p.on_seg(a, b) or q.on_seg(a, b) or
         a.on_seg(p, q) or b.on_seg(p, q);
}

point line_intersect(point p, point q, point a, point b) {
  point r = q-p, s = b-a, c(p%q, a%b);
  if (eq(r%s,0)) return point(INF, INF);
  return point(point(r.x, s.x) % c, point(r.y, s.y) % c) / abs(r%s);
}

// Sorting points in counterclockwise order.
// If the angle is the same, closer points to the origin come first.
point origin;
bool radial(point p, point q) {
  int dir = p.dir(origin, q);
  return dir > 0 or (!dir and p.on_seg(origin, q));
}

// Graham Scan
vector<point> convex_hull(vector<point> pts) {
  vector<point> ch;
  point mn = pts[0];

  for(point p : pts) if (p.y < mn.y or (p.y == mn.y and p.x < p.y)) mn = p;

  origin = mn;
  sort(pts.begin(), pts.end(), radial);

  int n = 0;

  // IF: Convex hull without colinear points
  for(point p : pts) {
    while (n > 1 and ch[n-1].dir(ch[n-2], p) < 1) n--;
    ch[n++] = p;
  }

  /* ELSE IF: Convex hull with colinear points
  for(point p : pts) {
    while (n > 1 and ch[n-1].dir(ch[n-2], p) < 0) n--;
    ch[n++] = p;
  }

  for(int i=pts.size()-1; i >=1; --i)
    if (pts[i] != ch[n-1] and !pts[i].dir(pts[0], ch[n-1]))
      ch[n++] = pts[i];
  // END IF */

  ch.resize(n);
  return ch;
}

// Double of the triangle area
ld double_of_triangle_area(point p1, point p2, point p3) {
  return abs((p2-p1) % (p3-p1));
}

bool point_inside_triangle(point p, point p1, point p2, point p3) {
  ld a1, a2, a3, a;
  a =  double_of_triangle_area(p1, p2, p3);
  a1 = double_of_triangle_area(p, p2, p3);
  a2 = double_of_triangle_area(p, p1, p3);
  a3 = double_of_triangle_area(p, p1, p2);
  return eq(a, a1 + a2 + a3);
}

bool point_inside_convex_poly(int l, int r, vector<point> v, point p) {
  while(l+1 != r) {
    int m = (l+r)/2;
    if (p.dir(v[0], v[m])) r = m;
    else l = m;
  }
  return point_inside_triangle(p, v[0], v[l], v[r]);
}

// TODO: find bug in this function
bool find_circle_intersection(point p1, ld r1, point p2, ld r2, point &a1, point &a2) {
  ld x, y;
  ld d = p1.dist(p2);
  if (d > r1 + r2) return 0;

  x = (r1*r1 - r2*r2 + d*d) / 2*d;
  y = sqrt(r1*r1 - x*x);
  a1 = point(x, y), a2 = point(x, -y);

  a1 = a1.rotate(p2 - p1) + p1;
  a2 = a2.rotate(p2 - p1) + p1;
  return 1;
}
