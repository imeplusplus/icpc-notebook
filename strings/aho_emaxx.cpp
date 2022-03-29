// Aho Corasick - <O(sum(m)), O(n + #matches)>
// Multiple string matching

#include <bits/stdc++.h>
using namespace std;

int remap(char c) {
  if (islower(c)) return c - 'a';
  return c - 'A' + 26;
}

const int K = 52;

struct Aho {
  struct Node {
    int nxt[K];
    int par = -1;
    int link = -1;
    int go[K];
    bitset<1005> ids;
    char pch;

    Node(int p = -1, char ch = '$') : par { p }, pch { ch } {
      fill(begin(nxt), end(nxt), -1);
      fill(begin(go), end(go), -1);
    }
  };

  vector<Node> nodes;

  Aho() : nodes (1) {}

  void add_string(const string& s, int id) {
    int u = 0;
    for (char ch : s) {
      int c = remap(ch);
      if (nodes[u].nxt[c] == -1) {
        nodes[u].nxt[c] = nodes.size();
        nodes.emplace_back(u, ch);
      }

      u = nodes[u].nxt[c];
    }

    nodes[u].ids.set(id);
  }

  int get_link(int u) {
    if (nodes[u].link == -1) {
      if (u == 0 or nodes[u].par == 0) nodes[u].link = 0;
      else nodes[u].link = go(get_link(nodes[u].par), nodes[u].pch);
    }
    return nodes[u].link;
  }

  int go(int u, char ch) {
    int c = remap(ch);
    if (nodes[u].go[c] == -1) {
      if (nodes[u].nxt[c] != -1) nodes[u].go[c] = nodes[u].nxt[c];
      else nodes[u].go[c] = (u == 0) ? 0 : go(get_link(u), ch);
      nodes[u].ids |= nodes[nodes[u].go[c]].ids;
    }
    return nodes[u].go[c];
  }

  bitset<1005> run(const string& s) {
    bitset<1005> bs;
    int u = 0;
    for (char ch : s) {
      int c = remap(ch);
      if (go(u, ch) == -1) assert(0);
      bs |= nodes[u].ids;
      u = nodes[u].nxt[c];
      if (u == -1) u = 0;
    }
    bs |= nodes[u].ids;
    return bs;
  }
};
