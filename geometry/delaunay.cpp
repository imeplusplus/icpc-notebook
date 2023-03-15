/*
Complexity: O(nlogn)
Code by Monogon: https://codeforces.com/blog/entry/85638
This code doesn't work when two points have the same x coordinate.
This is handled simply by rotating all input points by 1 radian and praying to the geometry gods.

The definition of the Voronoi diagram immediately shows signs of applications.
*   Given a set S of n points and m query points p1,...,pm, we can answer for each query point, its nearest neighbor in S.
    This can be done in O((n+q)log(n+q)) offline by sweeping the Voronoi diagram and query points.
    Or it can be done online with persistent data structures.

*   For each Delaunay triangle, its circumcircle does not strictly contain any points in S. (In fact, you can also consider this the defining property of Delaunay triangulation)

*   The number of Delaunay edges is at most 3n - 6, so there is hope for an efficient construction.

*   Each point p belongs to S is adjacent to its nearest neighbor with a Delaunay edge.

*   The Delaunay triangulation maximizes the minimum angle in the triangles among all possible triangulations.

*   The Euclidean minimum spanning tree is a subset of Delaunay edges.

*/

#include <bits/stdc++.h>
 
#define ll long long
#define sz(x) ((int) (x).size())
#define all(x) (x).begin(), (x).end()
#define vi vector<int>
#define pii pair<int, int>
#define rep(i, a, b) for(int i = (a); i < (b); i++)
using namespace std;
template<typename T>
using minpq = priority_queue<T, vector<T>, greater<T>>;
 
using ftype = long double;
const ftype EPS = 1e-12, INF = 1e100;
 
struct pt {
    ftype x, y;
    pt(ftype x = 0, ftype y = 0) : x(x), y(y) {}

    // vector addition, subtraction, scalar multiplication
    pt operator+(const pt &o) const {
        return pt(x + o.x, y + o.y);
    }
    pt operator-(const pt &o) const {
        return pt(x - o.x, y - o.y);
    }
    pt operator*(const ftype &f) const {
        return pt(x * f, y * f);
    }

    // rotate 90 degrees counter-clockwise
    pt rot() const {
        return pt(-y, x);
    }

    // dot and cross products
    ftype dot(const pt &o) const {
        return x * o.x + y * o.y;
    }
    ftype cross(const pt &o) const {
        return x * o.y - y * o.x;
    }

    // length
    ftype len() const {
        return hypotl(x, y);
    }

    // compare points lexicographically
    bool operator<(const pt &o) const {
        return make_pair(x, y) < make_pair(o.x, o.y);
    }
};

// check if two vectors are collinear. It might make sense to use a
// different EPS here, especially if points have integer coordinates
bool collinear(pt a, pt b) {
    return abs(a.cross(b)) < EPS;
}


// intersection point of lines ab and cd. Precondition is that they aren't collinear
pt lineline(pt a, pt b, pt c, pt d) {
    return a + (b - a) * ((c - a).cross(d - c) / (b - a).cross(d - c));
}

// circumcircle of points a, b, c. Precondition is that abc is a non-degenerate triangle.
pt circumcenter(pt a, pt b, pt c) {
    b = (a + b) * 0.5;
    c = (a + c) * 0.5;
    return lineline(b, b + (b - a).rot(), c, c + (c - a).rot());
}

// x coordinate of sweep-line
ftype sweepx;

// an arc on the beacah line is given implicitly by the focus p,
// the focus q of the following arc, and the position of the sweep-line.
struct arc {
    mutable pt p, q;
    mutable int id = 0, i;
    arc(pt p, pt q, int i) : p(p), q(q), i(i) {}

    // get y coordinate of intersection with following arc.
    // don't question my magic formulas
    ftype gety(ftype x) const {
        if(q.y == INF) return INF;
        x += EPS;
        pt med = (p + q) * 0.5;
        pt dir = (p - med).rot();
        ftype D = (x - p.x) * (x - q.x);
        return med.y + ((med.x - x) * dir.x + sqrtl(D) * dir.len()) / dir.y;
    }
    bool operator<(const ftype &y) const {
        return gety(sweepx) < y;
    }
    bool operator<(const arc &o) const {
        return gety(sweepx) < o.gety(sweepx);
    }
};

// the beach line will be stored as a multiset of arc objects
using beach = multiset<arc, less<>>;

// an event is given by
//     x: the time of the event
//     id: If >= 0, it's a point event for index id.
//         If < 0, it's an ID for a vertex event
//     it: if a vertex event, the iterator for the arc to be deleted
struct event {
    ftype x;
    int id;
    beach::iterator it;
    event(ftype x, int id, beach::iterator it) : x(x), id(id), it(it) {}
    bool operator<(const event &e) const {
        return x > e.x;
    }
};

struct fortune {
    beach line; // self explanatory
    vector<pair<pt, int>> v; // (point, original index)
    priority_queue<event> Q; // priority queue of point and vertex events
    vector<pii> edges; // delaunay edges
    vector<bool> valid; // valid[-id] == true if the vertex event with corresponding id is valid
    int n, ti; // number of points, next available vertex ID
    fortune(vector<pt> p) {
        n = sz(p);
        v.resize(n);
        rep(i, 0, n) v[i] = {p[i], i};
        sort(all(v)); // sort points by coordinate, remember original indices for the delaunay edges
    }
    // update the remove event for the arc at position it
    void upd(beach::iterator it) {
        if(it->i == -1) return; // doesn't correspond to a real point
        valid[-it->id] = false; // mark existing remove event as invalid
        auto a = prev(it);
        if(collinear(it->q - it->p, a->p - it->p)) return; // doesn't generate a vertex event
        it->id = --ti; // new vertex event ID
        valid.push_back(true); // label this ID true
        pt c = circumcenter(it->p, it->q, a->p);
        ftype x = c.x + (c - it->p).len();
        // event is generated at time x.
        // make sure it passes the sweep-line, and that the arc truly shrinks to 0
        if(x > sweepx - EPS && a->gety(x) + EPS > it->gety(x)) {
            Q.push(event(x, it->id, it));
        }
    }
    // add Delaunay edge
    void add_edge(int i, int j) {
        if(i == -1 || j == -1) return;
        edges.push_back({v[i].second, v[j].second});
    }
    // handle a point event
    void add(int i) {
        pt p = v[i].first;
        // find arc to split
        auto c = line.lower_bound(p.y);
        // insert new arcs. passing the following iterator gives a slight speed-up
        auto b = line.insert(c, arc(p, c->p, i));
        auto a = line.insert(b, arc(c->p, p, c->i));
        add_edge(i, c->i);
        upd(a); upd(b); upd(c);
    }
    // handle a vertex event
    void remove(beach::iterator it) {
        auto a = prev(it);
        auto b = next(it);
        line.erase(it);
        a->q = b->p;
        add_edge(a->i, b->i);
        upd(a); upd(b);
    }
    // X is a value exceeding all coordinates
    void solve(ftype X = 1e9) {
        // insert two points that will always be in the beach line,
        // to avoid handling edge cases of an arc being first or last
        X *= 3;
        line.insert(arc(pt(-X, -X), pt(-X, X), -1));
        line.insert(arc(pt(-X, X), pt(INF, INF), -1));
        // create all point events
        rep(i, 0, n) {
            Q.push(event(v[i].first.x, i, line.end()));
        }
        ti = 0;
        valid.assign(1, false);
        while(!Q.empty()) {
            event e = Q.top(); Q.pop();
            sweepx = e.x;
            if(e.id >= 0) {
                add(e.id);
            }else if(valid[-e.id]) {
                remove(e.it);
            }
        }
    }
};