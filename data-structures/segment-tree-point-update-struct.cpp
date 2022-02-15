// Segment Tree (range query and point update)
// Update - O(log n)
// Query - O(log n)
// Memory - O(n)

struct Node {
  ll val;
 
  Node(ll _val = 0) : val(_val) {}
  Node(const Node& l, const Node& r) : val(l.val + r.val) {}
 
  friend ostream& operator<<(ostream& os, const Node& a) {
    os << a.val;
    return os;
  }
};
 
template <class T = Node, class U = int>
struct SimpleSegTree {
  int n;
  vector<T> st;
 
  SimpleSegTree(int _n) : n(_n), st(4 * n) {}
 
  SimpleSegTree(vector<U>& v) : n((int)v.size()), st(4 * n) {
    build(v, 1, 0, n - 1);
  }
 
  void build(vector<U>& v, int p, int l, int r) {
    if (l == r) { st[p] = T(v[l]); return; }
    int mid = (l + r) / 2;
    build(v, 2 * p, l, mid);
    build(v, 2 * p + 1, mid + 1, r);
    st[p] = T(st[2 * p], st[2 * p + 1]);
  }
 
  T query(int i, int j, int p, int l, int r) {
    if (l >= i and j >= r) return st[p];
    if (l > j or r < i) return T();
    int mid = (l + r) / 2;
    return T(query(i, j, 2 * p, l, mid), query(i, j, 2 * p + 1, mid + 1, r));
  }
 
  T query(int i, int j) { return query(i, j, 1, 0, n - 1); }
 
  void update(int idx, U v, int p, int l, int r) {
    if (l == r) { st[p] = T(v); return; }
    int mid = (l + r) / 2;
    if (idx <= mid) update(idx, v, 2 * p, l, mid);
    else update(idx, v, 2 * p + 1, mid + 1, r);
    st[p] = T(st[2 * p], st[2 * p + 1]);
  }
 
  void update(int idx, U v) { update(idx, v, 1, 0, n - 1); }
};
