struct BIT {
  ll b[N]={};
  ll sum(int x) {
    ll r=0;
    for(x+=2;x;x-=x&-x)
      r += b[x];
    return r;
  }
  void upd(int x, ll v) {
    for(x+=2;x<N;x+=x&-x)
      b[x]+=v;
  }
};
struct BITRange {
  BIT a,b;
  ll sum(int x) {
    return a.sum(x)*x+b.sum(x);
  }
  void upd(int l, int r, ll v) {
    a.upd(l,v), a.upd(r+1,-v);
    b.upd(l,-v*(l-1)), b.upd(r+1,v*r);
  }
};
