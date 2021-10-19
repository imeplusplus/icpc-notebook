#include "basics.cpp"
//functions tested at: https://codeforces.com/group/3qadGzUdR4/contest/101706/problem/B

//WARNING: all distance functions are not realizing sqrt operation
//Suggestion: for line intersections check LineLineIntersection and then use ComputeLineIntersection

point ProjectPointLine(point c, point a, point b) {
    ld r = dot(b - a,b - a);
    if (fabs(r) < EPS) return a;
    return a + (b - a)*dot(c - a, b - a)/dot(b - a, b - a);
}

point ProjectPointRay(point c, point a, point b) {
    ld r = dot(b - a, b - a);
    if (fabs(r) < EPS) return a;
    r = dot(c - a, b - a) / r;
    if (le(r, 0)) return a;
    return a + (b - a)*r;
}

point ProjectPointSegment(point c, point a, point b) {
    ld r = dot(b - a, b - a);
    if (fabs(r) < EPS) return a;
    r = dot(c - a, b - a)/r;
    if (le(r, 0)) return a;
    if (ge(r, 1)) return b;
    return a + (b - a)*r;
}

ld DistancePointLine(point c, point a, point b) {
    return c.dist2(ProjectPointLine(c, a, b));
}

ld DistancePointRay(point c, point a, point b) {
    return c.dist2(ProjectPointRay(c, a, b));
}

ld DistancePointSegment(point c, point a, point b) {
    return c.dist2(ProjectPointSegment(c, a, b));
}

//not tested
ld DistancePointPlane(ld x, ld y, ld z,
                        ld a, ld b, ld c, ld d)
{
    return fabs(a*x + b*y + c*z - d)/sqrt(a*a + b*b + c*c);
}

bool LinesParallel(point a, point b, point c, point d) { 
    return fabs(cross(b - a, d - c)) < EPS; 
}

bool LinesCollinear(point a, point b, point c, point d) {
  return LinesParallel(a, b, c, d)
      && fabs(cross(a-b, a-c)) < EPS
      && fabs(cross(c-d, c-a)) < EPS; 
}

point lines_intersect(point p, point q, point a, point b) {
    point r = q - p, s = b - a, c(p%q, a%b);
    if (eq(r%s,0)) return point(LINF, LINF);
    return point(point(r.x, s.x) % c, point(r.y, s.y) % c) / (r%s);
}

//be careful: test LineLineIntersection before using this function
point ComputeLineIntersection(point a, point b, point c, point d) {
    b = b - a; d = c - d; c = c - a;
    assert(dot(b, b) > EPS && dot(d, d) > EPS);
    return a + b*cross(c, d)/cross(b, d);
}

bool LineLineIntersect(point a, point b, point c, point d) {
    if(!LinesParallel(a, b, c, d)) return true;
    if(LinesCollinear(a, b, c, d)) return true; 
    return false;
}


//rays in direction a -> b, c -> d
bool RayRayIntersect(point a, point b, point c, point d){
    if (a.dist2(c) < EPS || a.dist2(d) < EPS ||
        b.dist2(c) < EPS || b.dist2(d) < EPS) return true;
    if (LinesCollinear(a, b, c, d)) {
        if(ge(dot(b - a, d - c), 0)) return true;
        if(ge(dot(a - c, d - c), 0)) return true;
        return false;
    }
    if(!LineLineIntersect(a, b, c, d)) return false;
    point inters = lines_intersect(a, b, c, d);
    if(ge(dot(inters - c, d - c), 0) && ge(dot(inters - a, b - a), 0)) return true;
    return false;
}

bool SegmentSegmentIntersect(point a, point b, point c, point d) {
    if (a.dist2(c) < EPS || a.dist2(d) < EPS ||
        b.dist2(c) < EPS || b.dist2(d) < EPS) return true;
    int d1, d2, d3, d4;
    d1 = direction(a, b, c);
    d2 = direction(a, b, d);
    d3 = direction(c, d, a);
    d4 = direction(c, d, b);
    if (d1*d2 < 0 and d3*d4 < 0) return 1;
    return a.on_seg(c, d) or b.on_seg(c, d) or
            c.on_seg(a, b) or b.on_seg(c, d);
}

bool SegmentLineIntersect(point a, point b, point c, point d){
    if(!LineLineIntersect(a, b, c, d)) return false;
    point inters = lines_intersect(a, b, c, d);
    if(inters.on_seg(a, b)) return true;
    return false;
}

//ray in direction c -> d
bool SegmentRayIntersect(point a, point b, point c, point d){
    if (a.dist2(c) < EPS || a.dist2(d) < EPS ||
        b.dist2(c) < EPS || b.dist2(d) < EPS) return true;
    if (LinesCollinear(a, b, c, d)) {
        if(c.on_seg(a, b)) return true;
        if(ge(dot(d - c, a - c), 0)) return true;
        return false;
    }
    if(!LineLineIntersect(a, b, c, d)) return false;
    point inters = lines_intersect(a, b, c, d);
    if(!inters.on_seg(a, b)) return false;
    if(ge(dot(inters - c, d - c), 0)) return true;
    return false; 
}

//ray in direction a -> b
bool RayLineIntersect(point a, point b, point c, point d){
    if (a.dist2(c) < EPS || a.dist2(d) < EPS ||
        b.dist2(c) < EPS || b.dist2(d) < EPS) return true;
    if (!LineLineIntersect(a, b, c, d)) return false;
    point inters = lines_intersect(a, b, c, d);
    if(!LineLineIntersect(a, b, c, d)) return false;
    if(ge(dot(inters - a, b - a), 0)) return true;
    return false;
}

ld DistanceSegmentLine(point a, point b, point c, point d){
    if(SegmentLineIntersect(a, b, c, d)) return 0;
    return min(DistancePointLine(a, c, d), DistancePointLine(b, c, d));
}

ld DistanceSegmentRay(point a, point b, point c, point d){
    if(SegmentRayIntersect(a, b, c, d)) return 0;
    ld min1 = DistancePointSegment(c, a, b);
    ld min2 = min(DistancePointRay(a, c, d), DistancePointRay(b, c, d));
    return min(min1, min2);
}

ld DistanceSegmentSegment(point a, point b, point c, point d){
    if(SegmentSegmentIntersect(a, b, c, d)) return 0;
    ld min1 = min(DistancePointSegment(c, a, b), DistancePointSegment(d, a, b));
    ld min2 = min(DistancePointSegment(a, c, d), DistancePointSegment(b, c, d));
    return min(min1, min2);
}

ld DistanceRayLine(point a, point b, point c, point d){
    if(RayLineIntersect(a, b, c, d)) return 0;
    ld min1 = DistancePointLine(a, c, d);
    return min1;
}

ld DistanceRayRay(point a, point b, point c, point d){
    if(RayRayIntersect(a, b, c, d)) return 0;
    ld min1 = min(DistancePointRay(c, a, b), DistancePointRay(a, c, d));
    return min1;
}

ld DistanceLineLine(point a, point b, point c, point d){
    if(LineLineIntersect(a, b, c, d)) return 0;
    return DistancePointLine(a, c, d);
}
