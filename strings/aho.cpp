int p[N], sl[N], nxt[N][26], k[N], c[N];
int tsz=1; // size of the trie

void add(const string &s) {
  int cur = 1; // the first element of the trie is the root

  for (int i=0; s[i]; ++i) {
    int j = s[i] - 'a';
    if (!nxt[cur][j]) {
      tsz++;
      p[tsz] = cur;
      c[tsz] = j;
      nxt[cur][j] = tsz;
    }
    cur = nxt[cur][j];
  }

  k[cur]++;
}

void build() {
  queue<int> q;

  for(int i=0; i<26; ++i) {
    nxt[0][i] = 1;
    if (nxt[1][i]) q.push(nxt[1][i]);
  }

  while (!q.empty()) {
    int v = q.front(); q.pop();
    int u = sl[p[v]];

    while(u and !nxt[u][c[v]]) u = sl[u];
    sl[v] = nxt[u][c[v]];
    k[v] += k[sl[v]];

    for(int i=0; i<26; ++i) if (nxt[v][i])
      q.push(nxt[v][i]);
  }
}

int match(char *s) {
  int x = 1, ans = 0;
  for(int i=0; s[i]; ++i) {
    int t = s[i] - 'a';
    while(x and !nxt[x][t]) x = sl[x];
    x = nxt[x][t];
    sm += k[x];
  }
  return ans;
}
