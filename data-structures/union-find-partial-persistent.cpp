/**********************************************************************************
* DSU (DISJOINT SET UNION / UNION-FIND)                                           *
* Time complexity:  Unite - O(log n)                                              *
*                   Find - O(log n)                                               *
* Usage: find(node), unite(node1, node2), sz[find(node)]                          *
* Notation: par: vector of parents                                                *
*           sz:  vector of subsets sizes, i.e. size of the subset a node is in    *
*           his: history: time when it got a new parent                           *
*           t: current time                                                       *
**********************************************************************************/

int t, par[N], sz[N], his[N];

int find(int a, int t){
    if(par[a] == a) return a;
    if(his[a] > t) return a;
    return find(par[a], t);
}

void unite(int a, int b){
    if(find(a, t) == find(b, t)) return;
    a = find(a, t), b = find(b, t), t++;
    if(sz[a] < sz[b]) swap(a, b);
    sz[a] += sz[b], par[b] = a, his[b] = t;
}

//in main
for(int i = 0; i < N; i++) par[i] = i, sz[i] = 1, his[i] = 0;
