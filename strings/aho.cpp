// Aho Corasick - <O(sum(m)), O(n + #matches)>
// Multiple string matching

int p[N], f[N], nxt[N][26], ch[N];
int tsz=1; // size of the trie

int cnt[N]; // used to know number of matches

// used to know which strings matches.
// S is the number of strings. Can use set instead
const int S = 2e3+5;
bitset<S> elem[N];

void init() {
  tsz=1;
  memset(f, 0, sizeof(f));
  memset(nxt, 0, sizeof(nxt));
  memset(cnt, 0, sizeof(cnt));
  for (int i = 0; i < N; i++) elem[i].reset();
}

void add(const string &s, int x) {
  int cur = 1; // the first element of the trie is the root

  for (int i=0; s[i]; ++i) {
    int j = s[i] - 'a';
    if (!nxt[cur][j]) {
      tsz++;
      p[tsz] = cur;
      ch[tsz] = j;
      nxt[cur][j] = tsz;
    }
    cur = nxt[cur][j];
  }

  cnt[cur]++; //
  elem[cur].set(x);
}

void build() {
  queue<int> q;

  for(int i=0; i<26; ++i) {
    nxt[0][i] = 1;
    if (nxt[1][i]) q.push(nxt[1][i]);
  }

  while (!q.empty()) {
    int v = q.front(); q.pop();
    int u = f[p[v]];

    while (u and !nxt[u][ch[v]]) u = f[u];
    f[v] = nxt[u][ch[v]];
    cnt[v] += cnt[f[v]];

    for (int i = 0; i < 26; ++i) if (nxt[v][i])
      q.push(nxt[v][i]);
  }
}

// Return ans to get number of matches
// Return a map (or global array) if want to know how many of each string have matched
bitset<S> match(char *s) {
  int ans = 0;    // used to know the number of matches
  bitset<S> found; // used to know which strings matches

  int x = 1;
  for (int i = 0; s[i]; ++i) {
    int t = s[i] - 'a';
    while (x and !nxt[x][t]) x = f[x];
    x = nxt[x][t];

    // match found
    ans += cnt[x];
    found |= elem[x];
  }

  return found;
}

