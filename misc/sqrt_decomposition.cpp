// Square Root Decomposition (Mo's Algorithm) - O(n^(3/2))
const int N = 1e5+1, SQ = 500;
int n, m, v[N];

void add(int p) {}
void rem(int p) {}

struct query { int i, l, r, ans; } qs[N];

bool c1(query a, query b) { return a.l/SQ == b.l/SQ ? a.r < b.r : a.l < b.l; }
bool c2(query a, query b) { return a.i < b.i; }

int main() {
  sort(qs, qs+m, c1);

  int l = 0, r = -1;
  for (int i = 0; i < m; ++i) {
    query &q = qs[i];
    while (r < q.r) add(v[++r]);
    while (r > q.r) rem(v[r--]);
    while (l < q.l) rem(v[l++]);
    while (l > q.l) add(v[--l]);

    q.ans = /* calculate answer */;
  }


  sort(qs, qs+m, c2);
  for(int i=0; i<m; ++i) printf("%d\n", qs[i].ans);
  return 0;
}
