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

