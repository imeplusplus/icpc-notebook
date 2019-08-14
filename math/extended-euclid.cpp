// Extended Euclid: gcd(a, b) = x*a + y*b
// The solutions are:
// x = x0 + k*b/gcd
// y = y0 + k*a/gcd
void euclid(ll a, ll b, ll &x, ll &y, ll &d) {
  if (b) euclid(b, a%b, y, x, d), y -= x*(a/b);
  else x = 1, y = 0, d = a;
}

// Solves a*x + b*y = c
bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) {
  euclid(abs(a), abs(b), x0, y0, g);
  if (c % g) {
    return false;
  }

  x0 *= c / g;
  y0 *= c / g;
  if (a < 0) x0 = -x0;
  if (b < 0) y0 = -y0;
  return true;
}

// all x' and y' are a valid solution for any integer k
// x' = x + k*b/gcd
// y' = y - k*a/gcd
// Here a and b are actually a/gcd and b/gcd
void shift_solution (int & x, int & y, int a, int b, int cnt) {
  x += cnt * b;
  y -= cnt * a;
}

// Find the amount of solutions in a interval of x and y
int find_all_solutions (int a, int b, int c, int minx, int maxx, int miny, int maxy) {
  int x, y, g;
  if (! find_any_solution (a, b, c, x, y, g))
    return 0;
  a /= g;  b /= g;

  int sign_a = a>0 ? +1 : -1;
  int sign_b = b>0 ? +1 : -1;

  shift_solution (x, y, a, b, (minx - x) / b);
  if (x < minx)
    shift_solution (x, y, a, b, sign_b);
  if (x > maxx)
    return 0;
  int lx1 = x;

  shift_solution (x, y, a, b, (maxx - x) / b);
  if (x > maxx)
    shift_solution (x, y, a, b, -sign_b);
  int rx1 = x;

  shift_solution (x, y, a, b, - (miny - y) / a);
  if (y < miny)
    shift_solution (x, y, a, b, -sign_a);
  if (y > maxy)
    return 0;
  int lx2 = x;

  shift_solution (x, y, a, b, - (maxy - y) / a);
  if (y > maxy)
    shift_solution (x, y, a, b, sign_a);
  int rx2 = x;

  if (lx2 > rx2)
    swap (lx2, rx2);
  int lx = max (lx1, lx2);
  int rx = min (rx1, rx2);

  if (lx > rx) return 0;
  return (rx - lx) / abs(b) + 1;
}

//Solves
//t = a mod m1
//t = b mod m2
//ans = t mod lcm(m1, m2)
bool chinese_remainder(ll a, ll b, ll m1, ll m2, ll &ans, ll &lcm){
  ll x, y, g, c = b - a;
  euclid(m1, m2, x, y, g);
  if(c%g) return false;

  lcm = m1/g*m2;
  ans = ((a + c/g*x % (m2/g) * m1)%lcm + lcm)%lcm;
  return true;
}

// FIXME verify if it's correct!
// n statements: x == a_i mod b_i
ll norm(ll x, ll mod) { x %= mod; return x<0 ? x+mod : x; }

ll chinese(int n, int a[], int b[]) {
  ll ans = a[0], l = b[0];
  for (int i = 1; i < n; i++) {
    ll x, y, d;
    euclid(l, b[i], x, y, d);
    if ((a[i] - ans) % d != 0) {
      // no solution
      return -1;
    }

    ans = norm(ans + x * (a[i] - ans) / d % (b[i] / d) * l, l * b[i] / d);
    l = lcm(l, b[i]);
  }

  return ans;
}
