// Suffix Tree
// Build: O(|s|)
// Match: O(|p|)

template<int ALPHA_SIZE = 62>
struct SuffixTree {
  struct Node {
    int p, link = -1, l, r, nch = 0;
    vector<int> nxt;
    Node(int _l = 0, int _r = -1, int _p = -1) : p(_p), l(_l), r(_r), nxt(ALPHA_SIZE, -1) {}

    int len() { return r - l + 1; }
    int next(char ch) { return nxt[remap(ch)]; }

    // change this if different alphabet
    int remap(char c) {
      if (islower(c)) return c - 'a';
      if (isalpha(c)) return c - 'A' + 26;
      return c - '0' + 52;
    }

    void setEdge(char ch, int nx) {
      int c = remap(ch);
      if (nxt[c] != -1 and nx == -1) nch--;
      else if (nxt[c] == -1 and nx != -1) nch++;
      nxt[c] = nx;
    }
  };

  string s;
  long long num_diff_substr = 0;
  vector<Node> nodes;
  queue<int> leaves;
  pair<int, int> st = { 0, 0 };
  int ls = 0, rs = -1, n;

  int size() { return rs - ls + 1; }

  SuffixTree(string &_s) {
    s = _s;
    // Add this if you want every suffix to be a node
    // s += '$';
    n = (int)s.size();
    nodes.reserve(2 * n + 1);
    nodes.push_back(Node());
    //for (int i = 0; i < n; i++) extend();
  }

  pair<int, int> walk(pair<int, int> _st, int l, int r) {
    int u = _st.first;
    int d = _st.second;

    while (l <= r) {
      if (d == nodes[u].len()) {
        u = nodes[u].next(s[l]), d = 0;
        if (u == -1) return { u, d };
      } else {
        if (s[nodes[u].l + d] != s[l]) return { -1, -1 };
        if (r - l + 1 + d < nodes[u].len()) return { u, r - l + 1 + d };
        l += nodes[u].len() - d;
        d = nodes[u].len();
      }
    }

    return { u, d };
  }

  int split(pair<int, int> _st) {
    int u = _st.first;
    int d = _st.second;

    if (d == nodes[u].len()) return u;
    if (!d) return nodes[u].p;

    Node& nu = nodes[u];
    int mid = (int)nodes.size();
    nodes.push_back(Node(nu.l, nu.l + d - 1, nu.p));
    nodes[nu.p].setEdge(s[nu.l], mid);
    nodes[mid].setEdge(s[nu.l + d], u);
    nu.p = mid;
    nu.l += d;
    return mid;
  }

  int getLink(int u) {
    if (nodes[u].link != -1) return nodes[u].link;
    if (nodes[u].p == -1) return 0;
    int to = getLink(nodes[u].p);
    pair<int, int> nst = { to, nodes[to].len() };
    return nodes[u].link = split(walk(nst, nodes[u].l + (nodes[u].p == 0), nodes[u].r));
  }

  bool match(string &p) {
    int u = 0, d = 0;
    for (char ch : p) {
      if (d == min(nodes[u].r, rs) - nodes[u].l + 1) {
        u = nodes[u].next(ch), d = 1;
        if (u == -1) return false;
      } else {
        if (ch != s[nodes[u].l + d]) return false;
        d++;
      }
    }
    return true;
  }

  void extend() {
    int mid;
    assert(rs != n - 1);
    rs++;
    num_diff_substr += (int)leaves.size();
    do {
      pair<int, int> nst = walk(st, rs, rs);
      if (nst.first != -1) { st = nst; return; }
      mid = split(st);
      int leaf = (int)nodes.size();
      num_diff_substr++;
      leaves.push(leaf);
      nodes.push_back(Node(rs, n - 1, mid));
      nodes[mid].setEdge(s[rs], leaf);
      int to = getLink(mid);
      st = { to, nodes[to].len() };
    } while (mid);
  }

  void pop() {
    assert(ls <= rs);
    ls++;
    int leaf = leaves.front();
    leaves.pop();
    Node* nlf = &nodes[leaf];
    while (!nlf->nch) {
      if (st.first != leaf) {
        nodes[nlf->p].setEdge(s[nlf->l], -1);
        num_diff_substr -= min(nlf->r, rs) - nlf->l + 1;
        leaf = nlf->p;
        nlf = &nodes[leaf];
      } else {
        if (st.second != min(nlf->r, rs) - nlf->l + 1) {
          int mid = split(st);
          st.first = mid;
          num_diff_substr -= min(nlf->r, rs) - nlf->l + 1;
          nodes[mid].setEdge(s[nlf->l], -1);
          *nlf = nodes[mid];
          nodes[nlf->p].setEdge(s[nlf->l], leaf);
          nodes.pop_back();
        }
        break;
      }
    }

    if (leaf and !nlf->nch) {
      leaves.push(leaf);
      int to = getLink(nlf->p);
      pair<int, int> nst = { to, nodes[to].len() };
      st = walk(nst, nlf->l + (nlf->p == 0), nlf->r);
      nlf->l = rs - nlf->len() + 1;
      nlf->r = n - 1;
    }
  }
};
