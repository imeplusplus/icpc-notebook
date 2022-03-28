// Intersection of halfplanes - O(nlogn)
// Points are given in counterclockwise order
//
// by Agnez

typedef vector<point> polygon;

int cmp(ld x, ld y = 0, ld tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1; }

bool comp(point a, point b){
    if((cmp(a.x) > 0 || (cmp(a.x) == 0 && cmp(a.y) > 0) ) && (cmp(b.x) < 0 || (cmp(b.x) == 0 && cmp(b.y < 0)))) return 1;
    if((cmp(b.x) > 0 || (cmp(b.x) == 0 && cmp(b.y) > 0) ) && (cmp(a.x) < 0 || (cmp(a.x) == 0 && cmp(a.y < 0)))) return 0;
    ll R = a%b;
    if(R) return R > 0;
    return false;
}

namespace halfplane{
  struct L{
    point p,v;
    L(){}
    L(point P, point V):p(P),v(V){}
    bool operator<(const L &b)const{ return comp(v, b.v); }
  };
  vector<L> line;
  void addL(point a, point b){line.pb(L(a,b-a));}
  bool left(point &p, L &l){ return cmp(l.v % (p-l.p))>0; }
  bool left_equal(point &p, L &l){ return cmp(l.v % (p-l.p))>=0; }
  void init(){ line.clear(); }

  point pos(L &a, L &b){
    point x=a.p-b.p;
    ld t = (b.v % x)/(a.v % b.v);
    return a.p+a.v*t;
  }

  polygon intersect(){
    sort(line.begin(), line.end());
    deque<L> q; //linhas da intersecao
    deque<point> p; //pontos de intersecao entre elas
    q.push_back(line[0]);
    for(int i=1; i < (int) line.size(); i++){
      while(q.size()>1 && !left(p.back(), line[i]))
        q.pop_back(), p.pop_back();
      while(q.size()>1 && !left(p.front(), line[i]))
        q.pop_front(), p.pop_front();
      if(!cmp(q.back().v % line[i].v) && !left(q.back().p,line[i]))
        q.back() = line[i];
      else if(cmp(q.back().v % line[i].v))
        q.push_back(line[i]), p.push_back(point());
      if(q.size()>1)
        p.back()=pos(q.back(),q[q.size()-2]);
    }
    while(q.size()>1 && !left(p.back(),q.front()))
      q.pop_back(), p.pop_back();
    if(q.size() <= 2) return polygon(); //Nao forma poligono (pode nao ter intersecao)
    if(!cmp(q.back().v % q.front().v)) return polygon(); //Lados paralelos -> area infinita
    point ult = pos(q.back(),q.front());

    bool ok = 1;
    for(int i=0; i < (int) line.size(); i++)
      if(!left_equal(ult,line[i])){ ok=0; break; }

    if(ok) p.push_back(ult); //Se formar um poligono fechado
    polygon ret;
    for(int i=0; i < (int) p.size(); i++)
      ret.pb(p[i]);
    return ret;
  }
};

//
// Detect whether there is a non-empty intersection in a set of halfplanes
// Complexity O(n)
//
// By Agnez
//
pair<char, point> half_inter(vector<pair<point,point> > &vet){
	random_shuffle(all(vet));
	point p;
	rep(i,0,sz(vet)) if(ccw(vet[i].x,vet[i].y,p) != 1){
		point dir = (vet[i].y-vet[i].x)/abs(vet[i].y-vet[i].x);
		point l = vet[i].x - dir*1e15;
		point r = vet[i].x + dir*1e15;
		if(r<l) swap(l,r);
		rep(j,0,i){
			if(ccw(point(),vet[i].x-vet[i].y,vet[j].x-vet[j].y)==0){
				if(ccw(vet[j].x, vet[j].y, p) == 1)
					continue;
				return mp(0,point());
			}
			if(ccw(vet[j].x, vet[j].y, l) != 1)
				l = max(l, line_intersect(vet[i].x,vet[i].y,vet[j].x,vet[j].y));
			if(ccw(vet[j].x, vet[j].y, r) != 1)
				r = min(r, line_intersect(vet[i].x,vet[i].y,vet[j].x,vet[j].y));
			if(!(l<r)) return mp(0,point());
		}
		p=r;
	}
	return mp(1, p);
}
