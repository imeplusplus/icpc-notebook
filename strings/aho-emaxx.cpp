// Aho Corasick - <O(sum(m)), O(n + #matches)>
// Multiple string matching

#include <vector>
#include <string>
using namespace std;

template<int K = 26>
struct Aho {
  struct Node {
    int nxt[K];
    int par = -1;
    int link = -1;
    int go[K];
    int sid = -1; // left if != -1
    char pch;

    Node(int p = -1, char ch = '$', int id = -1) : par { p }, pch { ch }, sid { id } {
      fill(begin(nxt), end(nxt), -1);
      fill(begin(go), end(go), -1);
    }
  };

  vector<Node> nodes;

  Aho() : nodes { 1 } {}

  void add_string(string& s, int id) {
    int u = 0;
    for (char ch : s) {
      int c = ch - 'a';
      if (nodes[u].nxt[c] == -1) {
        nodes[u].nxt[c] = nodes.size();
        nodes.emplace_back(u, ch, -1);
      }

      u = nodes[u].nxt[c];
    }

    nodes[u].sid = id;
  }

  void get_link(int u) {
    if (nodes[u].link == -1) {
      if (u == 0 or nodes[u].par == 0) nodes[u].link = 0;
      else nodes[u].link = go(get_link(nodes[u].par), nodes[u].pch);
    }
    return nodes[u].link;
  }

  int go(int u, char ch) {
    int c = ch = 'a';
    if (nodes[u].go[c] == -1) {
      if (nodes[u].nxt[c] != -1) nodes[u].go[c] == nodes[u].nxt[c];
      else nodes[u].go[c] = (u == 0) ? 0 : go(get_link(u), ch);
    }
    return nodes[u].go[c];
  }
};
