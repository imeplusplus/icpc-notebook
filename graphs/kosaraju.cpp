/**********************************************************************************
* KOSARAJU'S ALGORITHM (GET EVERY STRONGLY CONNECTED COMPONENTS (SCC))            *
* Description: Given a directed graph, the algorithm generates a list of every    *
* strongly connected components. A SCC is a set of points in which you can reach  *
* every point regardless of where you start from. For instance, cycles can be     *
* a SCC themselves or part of a greater SCC.                                      *
* This algorithm starts with a DFS and generates an array called "ord" which      *
* stores vertices according to the finish times (i.e. when it reaches "return").  *
* Then, it makes a reversed DFS according to "ord" list. The set of points        *
* visited by the reversed DFS defines a new SCC.                                  *
* One of the uses of getting all SCC is that you can generate a new DAG (Directed *
* Acyclic Graph), easier to work with, in which each SCC being a "supernode" of   *
* the DAG.                                                                        *
* Time complexity: O(V+E)                                                         *
* Notation: adj[i]:   adjacency list for node i                                   *
*           adjt[i]:  reversed adjacency list for node i                          *
*           ord:      array of vertices according to their finish time            *
*           ordn:     ord counter                                                 *
*           scc[i]:   supernode assigned to i                                     *
*           scc_cnt:  amount of supernodes in the graph                           *
**********************************************************************************/
const int N = 2e5 + 5;

vector<int> adj[N], adjt[N];
int n, ordn, scc_cnt, vis[N], ord[N], scc[N];

//Directed Version
void dfs(int u) {
	vis[u] = 1;
	for (auto v : adj[u]) if (!vis[v]) dfs(v);
	ord[ordn++] = u;
}

void dfst(int u) {
	scc[u] = scc_cnt, vis[u] = 0;
	for (auto v : adjt[u]) if (vis[v]) dfst(v);
}

// add edge: u -> v
void add_edge(int u, int v){
	adj[u].push_back(v);
	adjt[v].push_back(u);
}

//Undirected version:
/*
	int par[N];

	void dfs(int u) {
		vis[u] = 1;
		for (auto v : adj[u]) if(!vis[v]) par[v] = u, dfs(v);
		ord[ordn++] = u;
	}

	void dfst(int u) {
		scc[u] = scc_cnt, vis[u] = 0;
		for (auto v : adj[u]) if(vis[v] and u != par[v]) dfst(v);
	}

	// add edge: u -> v
	void add_edge(int u, int v){
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

*/

// run kosaraju
void kosaraju(){
	for (int i = 1; i <= n; ++i) if (!vis[i]) dfs(i);
	for (int i = ordn - 1; i >= 0; --i) if (vis[ord[i]]) scc_cnt++, dfst(ord[i]);
}
