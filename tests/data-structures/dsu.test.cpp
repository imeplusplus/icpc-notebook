// @problem_url: https://www.spoj.com/problems/FRNDCIRC/
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5;

// @include: data-structures/dsu.cpp

int main() {
  int t;
  cin >> t;

  while (t--) {
    for (int i = 0; i < 1e5; i++) {
      par[i] = i;
      sz[i] = 1;
    }

    map<string, int> id;

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
      string a, b;
      cin >> a >> b;

      if (id.count(a) == 0) {
        id[a] = id.size();
      }

      if (id.count(b) == 0) {
        id[b] = id.size();
      }

      unite(id[a], id[b]);

      cout << sz[find(id[a])] << '\n';
    }
  }
}
