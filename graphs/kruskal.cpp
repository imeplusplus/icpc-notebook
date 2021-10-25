/**********************************************************************************
* KRUSKAL'S ALGORITHM (MINIMAL SPANNING TREE - INCREASING EDGE SIZE)              *
* Time complexity: O(ElogE)                                                       *
* Usage: cost, sz[find(node)]                                                     *
* Notation: cost: sum of all edges which belong to such MST                       *
*           sz:   vector of subsets sizes, i.e. size of the subset a node is in   *
**********************************************************************************/

// + Union-find

int cost = 0;
vector <pair<int, pair<int, int>>> edges; //mp(dist, mp(node1, node2))

int main () {
    // ...
    sort(edges.begin(), edges.end());
    for (auto e : edges)
        if (find(e.nd.st) != find(e.nd.nd))
            unite(e.nd.st, e.nd.nd), cost += e.st;

    return 0;
}
