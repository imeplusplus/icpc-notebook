// @problem_url: https://www.spoj.com/problems/NAJPF/
#include <bits/stdc++.h>
using namespace std;

// @include: strings/z.cpp

int main() {
  int t;
  cin >> t;
  while (t--) {
    string s, p;
    cin >> s >> p;

    int p_size = p.size();
    p.push_back('#');
    p.append(s);

    auto z = zfunction(p);

    vector<int> match;
    for (int i = p_size + 1; i < p.size(); i++) {
      if (z[i] == p_size) match.push_back(i - p_size);
    }

    if (match.empty()) {
      cout << "Not Found\n\n";
      continue;
    }

    cout << match.size() << '\n';

    for (auto x : match) cout << x << " ";
    cout << "\n\n";
  }
}