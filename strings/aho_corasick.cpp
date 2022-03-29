// Aho-Corasick

// Build: O(sum size of patterns)
// Find total number of matches: O(size of input string)
// Find number of matches for each pattern: O(num of patterns + size of input string)

// ids start from 0 by default!

template <int ALPHA_SIZE = 62>
struct Aho {
  struct Node {
    int p, char_p, link = -1, str_idx = -1, nxt[ALPHA_SIZE];
    bool has_end = false;
    Node(int _p = -1, int _char_p = -1) : p(_p), char_p(_char_p) {
      fill(nxt, nxt + ALPHA_SIZE, -1);
    }
  };

  vector<Node> nodes = { Node() };
  int ans, cnt = 0;
  bool build_done = false;
  vector<pair<int, int>> rep;
  vector<int> ord, occur, occur_aux;

  // change this if different alphabet
  int remap(char c) {
    if (islower(c)) return c - 'a';
    if (isalpha(c)) return c - 'A' + 26;
    return c - '0' + 52;
  }

  void add(string &p, int id = -1) {
    int u = 0;
    if (id == -1) id = cnt++;

    for (char ch : p) {
      int c = remap(ch);
      if (nodes[u].nxt[c] == -1) {
        nodes[u].nxt[c] = (int)nodes.size();
        nodes.push_back(Node(u, c));
      }

      u = nodes[u].nxt[c];
    }

    if (nodes[u].str_idx != -1) rep.push_back({ id, nodes[u].str_idx });
    else nodes[u].str_idx = id;
    nodes[u].has_end = true;
  }

  void build() {
    build_done = true;
    queue<int> q;

    for (int i = 0; i < ALPHA_SIZE; i++) {
      if (nodes[0].nxt[i] != -1) q.push(nodes[0].nxt[i]);
      else nodes[0].nxt[i] = 0;
    }

    while(q.size()) {
      int u = q.front();
      ord.push_back(u);
      q.pop();

      int j = nodes[nodes[u].p].link;
      if (j == -1) nodes[u].link = 0;
      else nodes[u].link = nodes[j].nxt[nodes[u].char_p];

      nodes[u].has_end |= nodes[nodes[u].link].has_end;

      for (int i = 0; i < ALPHA_SIZE; i++) {
        if (nodes[u].nxt[i] != -1) q.push(nodes[u].nxt[i]);
        else nodes[u].nxt[i] = nodes[nodes[u].link].nxt[i];
      }
    }
  }

  int match(string &s) {
    if (!cnt) return 0;
    if (!build_done) build();

    ans = 0;
    occur = vector<int>(cnt);
    occur_aux = vector<int>(nodes.size());

    int u = 0;
    for (char ch : s) {
      int c = remap(ch);
      u = nodes[u].nxt[c];
      occur_aux[u]++;
    }

    for (int i = (int)ord.size() - 1; i >= 0; i--) {
      int v = ord[i];
      int fv = nodes[v].link;
      occur_aux[fv] += occur_aux[v];
      if (nodes[v].str_idx != -1) {
        occur[nodes[v].str_idx] = occur_aux[v];
        ans += occur_aux[v];
      }
    }

    for (pair<int, int> x : rep) occur[x.first] = occur[x.second];
    return ans;
  }
};
