// Set of Intervals
// Use when you have disjoint intervals

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

#define pb push_back
#define st first
#define nd second

typedef pair<int, int> pii;
typedef pair<pii, int> piii;

int n, m, x, t;
set<piii> s;
set<pii> mosq;
vector<piii> frogs;
int c[N], len[N], p, b[N];

void in(int l, int r, int i) {
  vector<piii> add, rem;
  auto it = s.lower_bound({{l, 0}, 0});
  if(it != s.begin()) it--;
  for(; it != s.end(); it++) {
    int ll = it->st.st;
    int rr = it->st.nd;
    int idx = it->nd;

    if(ll > r) break;
    if(rr < l) continue;
    if(ll < l) add.pb({{ll, l-1}, idx});
    if(rr > r) add.pb({{r+1, rr}, idx});
    rem.pb(*it);
  }
  add.pb({{l, r}, i});
  for(auto x : rem) s.erase(x);
  for(auto x : add) s.insert(x);
}

void process(int l, int idx) {
  auto it2 = s.lower_bound({{l, 0}, 0});
  if(it2 != s.begin()) it2--;
  if(it2 != s.end() and it2->st.nd < l) it2++;
 
  mosq.insert({l, idx});
  if(it2 == s.end() or !(it2->nd)) return;
  
  vector<pii> rem;
  int ll = it2->st.st, rr = it2->st.nd, id = it2->nd;
  
  auto it = mosq.lower_bound({ll, 0});
  for(; it != mosq.end(); it++) {
    if(it->st > rr) break;
    c[id]++;
    len[id] += b[it->nd];
    rr += b[it->nd];
    rem.pb(*it);
  }
  for(auto x : rem) mosq.erase(x);
  in(ll, rr, id);
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for(int i = 1; i <= n; i++) {
    cin >> x >> t;
    len[i] = t;
    frogs.push_back({{x, x+t}, i});
  }
  s.insert({{0, int(1e9)}, 0});
  sort(frogs.begin(), frogs.end());
  for(int i = frogs.size() - 1; i >= 0; i--) 
    in(frogs[i].st.st, frogs[i].st.nd, frogs[i].nd);

  for(int i = 1; i <= m; i++) {
    cin >> p >> b[i];
    process(p, i);
  }

  for(int i = 1; i <= n; i++) cout << c[i] << " " << len[i] << "\n";
}
