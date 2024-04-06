// Tarjan for Block Cut Tree (Node Biconnected Componentes) - O(n + m)
#define pb push_back
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+5;

// Regular Tarjan stuff
int n, num[N], low[N], cnt, ch[N], art[N];
vector<int> adj[N], st;

int lb[N]; // Last block that node is contained
int bn; // Number of blocks
vector<int> blc[N]; // List of nodes from block

void dfs(int u, int p) {
	num[u] = low[u] = ++cnt;
	ch[u] = adj[u].size();
	st.pb(u);

	if (adj[u].size() == 1) blc[++bn].pb(u);

	for(int v : adj[u]) {
		if (!num[v]) {
			dfs(v, u), low[u] = min(low[u], low[v]);
			if (low[v] == num[u]) {
				if (p != -1 or ch[u] > 1) art[u] = 1;
				blc[++bn].pb(u);
				while(blc[bn].back() != v)
					blc[bn].pb(st.back()), st.pop_back();
			}
		}
		else if (v != p) low[u] = min(low[u], num[v]), ch[v]--;
	}

	if (low[u] == num[u]) st.pop_back();
}

// Nodes from 1 .. n are blocks
// Nodes from n+1 .. 2*n are articulations
vector<int> bct[2*N]; // Adj list for Block Cut Tree

void build_tree() {
	for(int u=1; u<=n; ++u) for(int v : adj[u]) if (num[u] > num[v]) {
		if (lb[u] == lb[v] or blc[lb[u]][0] == v) /* edge u-v belongs to block lb[u] */;
		else { /* edge u-v belongs to block cut tree */;
			int x = (art[u] ? u + n : lb[u]), y = (art[v] ? v + n : lb[v]);
			bct[x].pb(y), bct[y].pb(x);
		}
	}
}

void tarjan() {
	for(int u=1; u<=n; ++u) if (!num[u]) dfs(u, -1);
	for(int b=1; b<=bn; ++b) for(int u : blc[b]) lb[u] = b;
	build_tree();
}

