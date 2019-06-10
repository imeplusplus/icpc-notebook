#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

typedef long double ld;
const double EPS = 1e-9, PI = acos(-1.);

// Change long double to long long if using integers
typedef long double type;

//return -1: a < b, 0: a == b, 1: a > b
int comp(type a, type b) {
  return (a > b + EPS) - (a < b - EPS);
}

struct point {
  type x, y;

  point(type x = 0, type y = 0) : x(x), y(y) {}

  point operator -() { return point(-x, -y); }
  point operator +(point p) { return point(x+p.x, y+p.y); }
  point operator -(point p) { return point(x-p.x, y-p.y); }

  point operator *(type k) { return point(k*x, k*y); }
  point operator /(type k) { return point(x/k, y/k); }

  type operator *(point p) { return x*p.x + y*p.y; }
  type operator %(point p) { return x*p.y - y*p.x; }
  type operator !() {return (*this)*(*this); };

  bool onSegment(point a, point b) {
    if(comp((*this-a)%(b-a), 0)) return 0;
    return (comp(x, min(a.x, b.x)) >= 0 and
            comp(x, max(a.x, b.x)) <= 0 and
            comp(y, min(a.y, b.y)) >= 0 and
            comp(y, max(a.y, b.y)) <= 0);
  }
};

ostream &operator<<(ostream &os, const point &p) {
  os << "(" << p.x << ", " << p.y << ")";
  return os;
}

point rotateCCW(point p, ld t) {
  return point(p.x*cos(t)-p.y*sin(t), p.x*sin(t)+p.y*cos(t)); 
}

point rot90CCW (point p1) { return point(-p1.y, p1.x); }
point rot90CW (point p1) { return point(p1.y, -p1.x); }

point projectPointOnLine(point p, point a, point b) {
  return a + (b-a)*((p-a)*(b-a))/((b-a)*(b-a));
}

point projectPointSegment(point p, point a, point b) {
  ld r = (b-a)*(b-a);
  if(abs(r) < EPS) return a;
  r = ((p-a)*(b-a))/r;
  if(r < 0) return a;
  if(r > 1) return b;
  return a + (b-a)*r;
}

ld distPointSegment(point p, point a, point b) {
  return sqrt(!(projectPointSegment(p, a, b) - p));
}

// compute distance between point (x,y,z) and plane ax+by+cz=d
ld distPointPlane(ld x, ld y, ld z,
                      ld a, ld b, ld c, ld d) {
  return abs(a*x+b*y+c*z-d)/sqrt(a*a+b*b+c*c);
}

bool linesCollinear(point a, point b, point c, point d) {
  return abs((a-b)%(c-d)) < EPS and
         abs((a-b)%(a-c)) < EPS;
}

bool segmentIntersect(point a, point b, point c, point d) {
  if(linesCollinear(a, b, c, d)) {
    if (!(a - c) < EPS or !(a - d) < EPS or
        !(b - c) < EPS or !(b - d) < EPS) return true;
    if ((c-a)*(c-b) > 0 && (d-a)*(d-b) > 0 && (c-b)*(d-b) > 0)
      return false;
    return true;
  }
  //overflow
  if (((d-a)%(b-a)) * ((c-a)%(b-a)) > 0) return false;
  if (((a-c)%(d-c)) * ((b-c)%(d-c)) > 0) return false;
  return true;
}

point lineIntersection(point a, point b, point c, point d) {
  b = b-a; d = c-d; c = c-a;
  return a + b*(c%d)/(b%d);
}

point circumcircle(point a, point b, point c) {
  point u = rot90CW(b-a);
  point v = rot90CW(c-a);
  point n = (c-b)/2;
  return ((a+c)/2) + (v*((u%n)/(v%u)));
}

// Sorting points in counterclockwise order.
// If the angle is the same, closer points to the origin come first.
point origin;
bool radial(point a, point b) {
  double cp = (a - origin)%(b - origin);
  return abs(cp) < EPS ? !(a - origin) < !(b - origin) : cp > 0;
}

// Graham Scan
vector<point> convex_hull(vector<point> &pts) {
  vector<point> ch(pts.size());
  point mn = pts[0];

  for(point p : pts) if (p.y < mn.y or (p.y == mn.y and p.x < p.y)) mn = p;

  origin = mn;
  sort(pts.begin(), pts.end(), radial);

  int n = 0;

  // IF: Convex hull without collinear points
  for(point p : pts) {
    while (n > 1 and (ch[n - 1] - ch[n - 2])%(p - ch[n - 2]) < EPS) n--;
    ch[n++] = p;
  }

  /* ELSE IF: Convex hull with collinear points
  for(point p : pts) {
    while (n > 1 and (ch[n - 1] - ch[n - 2])%(p - ch[n - 2]) < -EPS) n--;
    ch[n++] = p;
  }

  for(int i=pts.size()-1; i >=1; --i)
    if (pts[i] != ch[n-1] and !pts[i].dir(pts[0], ch[n-1]))
      ch[n++] = pts[i];
  // END IF */

  ch.resize(n);
  return ch;
}

//Shoe Lace
double signedArea(vector<point> &p){
  double area = 0;
  for(int i = 0; i < p.size(); i++) {
    int j = (i+1) % p.size();
    area += p[i]%p[j];
  }
  return area / 2.0;
}

// TODO: test this code. This code has not been tested, please do it before proper use.
// http://codeforces.com/problemset/problem/975/E is a good problem for testing.
point centroid(vector<point> &p) {
  point c;
  double scale = 6.0 * signedArea(p);
  for (int i = 0; i < p.size(); i++){
    int j = (i+1) % p.size();
    c = c + (p[i]+p[j])*(p[i].x*p[j].y - p[j].x*p[i].y);
  }
  return c / scale;
}

// Random on border
bool pointInPolygon(const vector<point> &p, point q) {
  bool c = 0;
  for (int i = 0; i < p.size(); i++){
    int j = (i+1)%p.size();
    if ((p[i].y <= q.y && q.y < p[j].y || 
      p[j].y <= q.y && q.y < p[i].y) &&
      q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y))
      c = !c;
  }
  return c;
}

// compute intersection of line through points a and b with
// circle centered at c with radius r > 0
vector<point> circleLineIntersection(point a, point b, point c, double r) {
  vector<point> ret;
  b = b-a;
  a = a-c;
  double A = b*b;
  double B = a*b;
  double C = a*a - r*r;
  double D = B*B - A*C;
  if (D < -EPS) return ret;
  ret.push_back(c+a+b*(-B+sqrt(D+EPS))/A);
  if (D > EPS)
    ret.push_back(c+a+b*(-B-sqrt(D))/A);
  return ret;
}

// compute intersection of circle centered at a with radius r
// with circle centered at b with radius R
vector<point> circleCircleIntersection(point c1, point c2, double r1, double r2) {
  vector<point> ret;
  double d = sqrt(!(c1 - c2));
  if (d > r1+r2 || d+min(r1, r2) < max(r1, r2)) return ret;
  double x = (d*d-r2*r2+r1*r1)/(2*d);
  double y = sqrt(r1*r1-x*x);
  point v = (c2-c1)/d;
  ret.push_back(c1 + v*x + rotateCCW(v, PI/2)*y);
  if (y > 0)
    ret.push_back(c1 + v*x - rotateCCW(v, PI/2)*y);
  return ret;
}

// tests whether or not a given polygon (in CW or CCW order) is simple
bool isSimple(const vector<point> &p) {
  for (int i = 0; i < p.size(); i++) {
    for (int k = i+1; k < p.size(); k++) {
      int j = (i+1) % p.size();
      int l = (k+1) % p.size();
      if (i == l || j == k) continue;
      if (segmentIntersect(p[i], p[j], p[k], p[l])) 
        return false;
    }
  }
  return true;
}

int main(){
  return 0;
}
