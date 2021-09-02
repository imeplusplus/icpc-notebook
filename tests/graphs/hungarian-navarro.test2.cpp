// @problem_url: https://codeforces.com/gym/101635/problem/G
#include <bits/stdc++.h>
using namespace std;

// @include: graphs/hungarian-navarro.cpp

const int N = 2e3 + 5;

int n, m;
pair<int, int> b[N], c[N], rest;

int main(){
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> b[i].first >> b[i].second;
  for (int i = 0; i < m; i++) cin >> c[i].first >> c[i].second;
  cin >> rest.first >> rest.second;
 
  auto h = Hungarian<false, int, true> (n + m - 1, n);
 
  int ans = 0;
  for (int i = 0; i < n; i++) ans += abs(rest.first - b[i].first) + abs(rest.second - b[i].second);
 
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n + m - 1; j++) {
      if (j < m) h.update(j, i, abs(b[i].first - c[j].first) + abs(b[i].second - c[j].second));
      else h.update(j, i, abs(rest.first - b[i].first) + abs(rest.second - b[i].second));
    }
  }
 
  cout << (ans + h.run()) << "\n";
 
  return 0;
}