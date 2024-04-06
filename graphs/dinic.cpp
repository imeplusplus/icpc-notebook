// Dinic - O(V^2 * E)
// Bipartite graph or unit flow - O(sqrt(V) * E)
// Small flow - O(F * (V + E))
// USE INF = 1e9!

/**********************************************************************************
* DINIC (FIND MAX FLOW / BIPARTITE MATCHING)                                      *
* Time complexity: O(EV^2)                                                        *
* Usage: dinic()                                                                  *
*        add_edge(from, to, capacity)                                             *
* Testcase:                                                                       *
* add_edge(src, 1, 1);   add_edge(1, snk, 1);   add_edge(2, 3, INF);              *
* add_edge(src, 2, 1);   add_edge(2, snk, 1);   add_edge(3, 4, INF);              *
* add_edge(src, 2, 1);   add_edge(3, snk, 1);                                     *
* add_edge(src, 2, 1);   add_edge(4, snk, 1);   => dinic() = 4                    *
**********************************************************************************/

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+1, INF = 1e9;
struct edge {int v, c, f;};

int n, src, snk, h[N], ptr[N];
vector<edge> edgs;
vector<int> g[N];

void add_edge (int u, int v, int c) {
	int k = edgs.size();
	edgs.push_back({v, c, 0});
	edgs.push_back({u, 0, 0});
	g[u].push_back(k);
	g[v].push_back(k+1);
}

void clear() {
		memset(h, 0, sizeof h);
		memset(ptr, 0, sizeof ptr);
		edgs.clear();
		for (int i = 0; i < N; i++) g[i].clear();
		src = 0;
		snk = N-1;
}

bool bfs() {
	memset(h, 0, sizeof h);
	queue<int> q;
	h[src] = 1;
	q.push(src);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(int i : g[u]) {
			int v = edgs[i].v;
			if (!h[v] and edgs[i].f < edgs[i].c)
				q.push(v), h[v] = h[u] + 1;
		}
	}
	return h[snk];
}

int dfs (int u, int flow) {
	if (!flow or u == snk) return flow;
	for (int &i = ptr[u]; i < g[u].size(); ++i) {
		edge &dir = edgs[g[u][i]], &rev = edgs[g[u][i]^1];
		int v = dir.v;
		if (h[v] != h[u] + 1)  continue;
		int inc = min(flow, dir.c - dir.f);
		inc = dfs(v, inc);
		if (inc) {
			dir.f += inc, rev.f -= inc;
			return inc;
		}
	}
	return 0;
}

int dinic() {
	int flow = 0;
	while (bfs()) {
		memset(ptr, 0, sizeof ptr);
		while (int inc = dfs(src, INF)) flow += inc;
	}
	return flow;
}

//Recover Dinic
void recover(){
	for(int i = 0; i < edgs.size(); i += 2){
		//edge (u -> v) is being used with flow f
		if(edgs[i].f > 0) {
			int v = edgs[i].v;
			int u = edgs[i^1].v;
		}
	}
}

/***********************************************************************************************
* FLOW WITH DEMANDS                                                                            *
*                                                                                              *
* 1 - Finding an arbitrary flow                                                                *
* Assume a network with [L, R] on edges (some may have L = 0), let's call it old network.      *
* Create a New Source and New Sink (this will be the src and snk for Dinic).                   *
* Modelling Network:                                                                           *
* 1) Every edge from the old network will have cost R - L                                      *
* 2) Add an edge from New Source to every vertex v with cost:                                  *
*    Sum(L) for every (u, v). (sum all L that LEAVES v)                                        *
* 3) Add an edge from every vertex v to New Sink with cost:                                    *
*    Sum(L) for every (v, w). (sum all L that ARRIVES v)                                       *
* 4) Add an edge from Old Source to Old Sink with cost INF (circulation problem)               *
* The Network will be valid if and only if the flow saturates the network (max flow == sum(L)) *
*                                                                                              *
* 2 - Finding Min Flow                                                                         *
* To find min flow that satisfies just do a binary search in the (Old Sink -> Old Source) edge *
* The cost of this edge represents all the flow from old network                               *
* Min flow = Sum(L) that arrives in Old Sink + flow that leaves (Old Sink -> Old Source)       *
************************************************************************************************/


int main () {
		clear();
		return 0;
}