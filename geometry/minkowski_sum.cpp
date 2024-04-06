#include "basics.cpp"
#include "polygons.cpp"

//ITA MINKOWSKI

typedef vector<point> polygon;

/*
 * Minkowski sum
	 Distance between two polygons P and Q:
		Do Minkowski(P, Q)
		Ans = min(ans, dist((0, 0), edge))
 */

polygon minkowski(polygon & A, polygon & B) {
	polygon P; point v1, v2;
	sort_lex_hull(A), sort_lex_hull(B);
	int n1 = A.size(), n2 = B.size();
	P.push_back(A[0] + B[0]);
	for(int i = 0, j = 0; i < n1 || j < n2;) {
		v1 = A[(i + 1)%n1] - A[i%n1];
		v2 = B[(j + 1)%n2] - B[j%n2];
		if (j == n2 || cross(v1, v2) > EPS) {
			P.push_back(P.back() + v1); i++;
		}
		else if (i == n1 || cross(v1, v2) < -EPS) {
			P.push_back(P.back() + v2); j++;
		}
		else {
			P.push_back(P.back() + (v1 + v2));
			i++; j++;
		}
	}
	P.pop_back();
	sort_lex_hull(P);
	return P;
}

// Given two polygons, returns the minkowski sum of them.
//
// By Agnez
bool comp(point a, point b){
	if((a.x > 0 || (a.x==0 && a.y>0) ) && (b.x < 0 || (b.x==0 && b.y<0))) return 1;
	if((b.x > 0 || (b.x==0 && b.y>0) ) && (a.x < 0 || (a.x==0 && a.y<0))) return 0;
	ll R = a%b;
	if(R) return R > 0;
	return a*a < b*b;
}

polygon poly_sum(polygon a, polygon b){
	//Lembre de nao ter pontos repetidos
	//	passar poligonos ordenados
	//	se nao tiver pontos colineares, pode usar:
	//pivot = *min_element(all(a));
	//sort(all(a),radialcomp);
	//a.resize(unique(all(a))-a.begin());
	//pivot = *min_element(all(b));
	//sort(all(b),radialcomp);
	//b.resize(unique(all(b))-b.begin());
	if(!sz(a) || !sz(b)) return polygon(0);
	if(min(sz(a),sz(b)) < 2){
		polygon ret(0);
		rep(i,0,sz(a)) rep(j,0,sz(b)) ret.pb(a[i]+b[j]);
		return ret;
	}
	polygon ret;
	ret.pb(a[0]+b[0]);
	int pa = 0, pb = 0;
	while(pa < sz(a) || pb < sz(b)){
		point p = ret.back();
		if(pb == sz(b) || (pa < sz(a) && comp((a[(pa+1)%sz(a)]-a[pa]),(b[(pb+1)%sz(b)]-b[pb]))))
			p = p + (a[(pa+1)%sz(a)]-a[pa]), pa++;
		else p = p + (b[(pb+1)%sz(b)]-b[pb]), pb++;
		//descomentar para tirar pontos colineares (o poligono nao pode ser degenerado)
//		while(sz(ret) > 1 && !ccw(ret[sz(ret)-2], ret[sz(ret)-1], p)) 
//			ret.pop_back();
		ret.pb(p);
	}
	assert(ret.back() == ret[0]);
	ret.pop_back();
	return ret;
}
