/**********************************************************************************
* DSU (DISJOINT SET UNION / UNION-FIND)                                           *
* Time complexity:  Unite - O(alpha n)                                            *
*                   Rollback - O(1)                                               *
*                   Find - O(alpha n)                                             *
* Usage: find(node), unite(node1, node2), sz[find(node)]                          *
* Notation: par: vector of parents                                                *
*           sz:  vector of subsets sizes, i.e. size of the subset a node is in    *
*           sp:  stack containing node and par from last op                       *
*           ss:  stack containing node and size from last op                      *
**********************************************************************************/

int par[N], sz[N];
stack <pii> sp, ss;

int find (int a) { return par[a] == a ? a : find(par[a]); }

void unite (int a, int b) {
    if ((a = find(a)) == (b = find(b))) return;
    if (sz[a] < sz[b]) swap(a, b);
    ss.push({a, sz[a]});
    sp.push({b, par[b]});
    sz[a] += sz[b];
    par[b] = a;
}

void rollback() {
    par[sp.top().st] = sp.top().nd; sp.pop();
    sz[ss.top().st]  = ss.top().nd; ss.pop();
}

int main(){
    for (int i = 0; i < N; i++) par[i] = i, sz[i] = 1;
    return 0;
}