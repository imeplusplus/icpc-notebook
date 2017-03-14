struct SegTree2D {
  int n,m;
  int st[4*N][4*N], a[N][N];
  void init(int _n, int _m) {
    n=_n,m=_m;
    build_x(1,0,n-1);
  }
  void build_x(int px, int lx, int rx) {
    if(lx!=rx) {
      int mx=(lx+rx)/2;
      build_x(2*px,lx,mx);
      build_x(2*px+1,mx+1,rx);
    }
    build_y(px,lx,rx,1,0,m-1);
  }
  void build_y(int px, int lx, int rx, int py, int ly, int ry) {
    if(ly==ry)
      if(lx==rx)
        st[px][py]=a[lx][ly];
      else
        st[px][py]=min(st[2*px][py],st[2*px+1][py]); //+
    else {
      int my=(ly+ry)/2;
      build_y(px,lx,rx,2*py,ly,my);
      build_y(px,lx,rx,2*py+1,my+1,ry);
      st[px][py]=min(st[px][2*py],st[px][2*py+1]); //+
    }
  }
  int qry_x(int px, int lx, int rx, int ix, int jx, int iy, int jy) {
    if(lx > jx or rx < ix) return INF; //0
    else if(lx >= ix and rx <= jx) return qry_y(px,1,0,m-1,iy,jy);
    int mx=(lx+rx)/2;
    return min(qry_x(2*px,lx,mx,ix,jx,iy,jy), qry_x(2*px+1,mx+1,rx,ix,jx,iy,jy)); //+
  }
  int qry_y(int px, int py, int ly, int ry, int iy, int jy) {
    if(ly > jy or ry < iy) return INF; //0
    else if(ly >= iy and ry <= jy) return st[px][py];
    int my=(ly+ry)/2;
    return min(qry_y(px,2*py,ly,my,iy,jy), qry_y(px,2*py+1,my+1,ry,iy,jy)); //+
  }
  void upd_x(int px, int lx, int rx, int x, int y, int v) {
    if(lx > x or rx < x) return;
    if(lx < rx) {
      int mx=(lx+rx)/2;
      upd_x(2*px,lx,mx,x,y,v);
      upd_x(2*px+1,mx+1,rx,x,y,v);
    }
    upd_y(px,lx,rx,1,0,m-1,x,y,v);
  }
  void upd_y(int px, int lx, int rx, int py, int ly, int ry, int x, int y, int v) {
    if(ly > y or ry < y) return;
    if(ly == ry)
      if(lx == rx)
        st[px][py]+=v,a[lx][ly]+=v; //=
      else
        st[px][py]=min(st[2*px][py],st[2*px+1][py]); //+
    else {
      int my=(ly+ry)/2;
      upd_y(px,lx,rx,2*py,ly,my,x,y,v);
      upd_y(px,lx,rx,2*py+1,my+1,ry,x,y,v);
      st[px][py]=min(st[px][2*py],st[px][2*py+1]); //+
    }
  }
  void upd(int x, int y, int v) { upd_x(1,0,n-1,x,y,v); }
  int qry(int lx, int ly, int rx, int ry) { return qry_x(1,0,n-1,lx,rx,ly,ry); }
};
