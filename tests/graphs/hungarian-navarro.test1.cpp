// @problem_url: https://codeforces.com/group/kZPk3ZTzR5/contest/102346/problem/G  
#include <bits/stdc++.h>
using namespace std;

// @include: graphs/hungarian-navarro.cpp

int n, m;
long double x;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  auto h = HungarianMult<true, true> (n, n);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> x;
      h.update(i, j, x);
    }
  }

  h.run();
  for (int i = 0; i < n; i++) cout << h.pairV[i] + 1 << " \n"[i == n - 1];
}