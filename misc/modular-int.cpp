// Struct to do basic modular arithmetic

template <int MOD>
struct Modular {
  int v;

  static int minv(int a, int m) {
    a %= m;
    assert(a);
    return a == 1 ? 1 : int(m - ll(minv(m, a)) * ll(m) / a);
  }

  Modular(ll _v = 0) : v(int(_v % MOD)) { 
    if (v < 0) v += MOD; 
  }

  bool operator==(const Modular& b) const { return v == b.v; }
  bool operator!=(const Modular& b) const { return v != b.v; }

  friend Modular inv(const Modular& b) { return Modular(minv(b.v, MOD)); }

  friend ostream& operator<<(ostream& os, const Modular& b) { return os << b.v; }
  friend istream& operator>>(istream& is, Modular& b) { 
    ll _v; 
    is >> _v; 
    b = Modular(_v); 
    return is; 
  }

  Modular operator+(const Modular& b) const { 
    Modular ans;
    ans.v = v >= MOD - b.v ? v + b.v - MOD : v + b.v;
    return ans;
  }

  Modular operator-(const Modular& b) const { 
    Modular ans;
    ans.v = v < b.v ? v - b.v + MOD : v - b.v; 
    return ans;
  }

  Modular operator*(const Modular& b) const { 
    Modular ans;
    ans.v = int(ll(v) * ll(b.v) % MOD);
    return ans;
  }

  Modular operator/(const Modular& b) const { 
    return (*this) * inv(b);
  }

  Modular& operator+=(const Modular& b) { return *this = *this + b; } 
  Modular& operator-=(const Modular& b) { return *this = *this - b; } 
  Modular& operator*=(const Modular& b) { return *this = *this * b; } 
  Modular& operator/=(const Modular& b) { return *this = *this / b; } 
};

using Mint = Modular<MOD>;
