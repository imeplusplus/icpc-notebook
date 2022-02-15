// Color Update - O(q log n)
// Heavily inspired by Um_nik's implementation
// q -> number of inserts

struct ColorUpdate {
  struct Seg {
    int l, r, c;
    Seg(int _l = 0, int _r = 0, int _c = 0) : l(_l), r(_r), c(_c) {};
    bool operator<(const Seg& b) const { return l < b.l; }
  };

  set<Seg> segs;

  void cut(int x) {
    auto it = segs.lower_bound({ x, 0, 0 });
    if (it == segs.begin()) return;
    it--;
    if (it->r == x - 1) return;
    Seg s = *it;
    segs.erase(it);
    segs.insert(Seg(s.l, x - 1, s.c));
    segs.insert(Seg(x, s.r, s.c));
  }

  void add(int l, int r, int c) {
    cut(l), cut(r + 1);
    Seg s(l, r, c);
    auto it = segs.lower_bound(s);
    while (it != segs.end() and it->l <= s.r) {
      auto it2 = it++;
      segs.erase(it2);
    }
    segs.insert(s);
  }
};
