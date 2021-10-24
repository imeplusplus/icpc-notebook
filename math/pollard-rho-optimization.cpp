// We recomend you to use pollard-rho.cpp! I've never needed this code, but here it is.
// This uses Brent's algorithm for cycle detection
//
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());

ull func(ull x, ull n, ull c) { return (mulmod(x, x, n) + c) % n; // f(x) = (x^2 + c) % n; }

ull pollard(ull n) {
  // Finds a positive divisor of n
  ull x, y, d, c;
  ull pot, lam;
  if(n % 2 == 0) return 2;
  if(isprime(n)) return n;

  while(1) {
    y = x = 2; d = 1;
    pot = lam = 1;
    while(1) {
      c = rng() % n;
      if(c != 0 and (c+2)%n != 0) break;
    }
    while(1) {
      if(pot == lam) {
        x = y;
        pot <<= 1;
        lam = 0;
      }
      y = func(y, n, c);
      lam++;
      d = gcd(x >= y ? x-y : y-x, n);
      if (d > 1) {
        if(d == n) break;
        else return d;
      }
    }
  }
}

void fator(ull n, vector<ull> &v) {
  // prime factorization of n, put into a vector v.
  //
  // for each prime factor of n, it is repeated the amount of times
  // that it divides n
  //
  // ex : n == 120, v = {2, 2, 2, 3, 5};
  // 
  //
  if(isprime(n)) { v.pb(n); return; }
  vector<ull> w, t; w.pb(n); t.pb(1);

  while(!w.empty()) {
    ull bck = w.back();
    ull div = pollard(bck);

    if(div == w.back()) {
      int amt = 0;
      for(int i=0; i < (int) w.size(); i++) {
        int cur = 0;
        while(w[i] % div == 0) {
          w[i] /= div;
          cur++;
        }
        amt += cur * t[i];
        if(w[i] == 1) {
          swap(w[i], w.back());
          swap(t[i], t.back());
          w.pop_back();
          t.pop_back();
        }
      }
      while(amt--) v.pb(div);
    }
    else {
      int amt = 0;
      while(w.back() % div == 0) {
        w.back() /= div;
        amt++;
      }
      amt *= t.back();
      if(w.back() == 1) {
        w.pop_back();
        t.pop_back();
      }

      w.pb(div);
      t.pb(amt);
    }
  }

  // the divisors will not be sorted, so you need to sort it afterwards
  sort(v.begin(), v.end());
}
