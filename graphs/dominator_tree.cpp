// a node u is said to be dominating node v if, from every path from the entry point to v you have to pass through u
// so this code is able to find every dominator from a specific entry point (usually 1)
// for directed graphs obviously

const int N = 1e5 + 7;

vector<int> adj[N], radj[N], tree[N], bucket[N];
int sdom[N], par[N], dom[N], dsu[N], label[N], arr[N], rev[N], cnt;

void dfs(int u) {
	cnt++;
	arr[u] = cnt;
	rev[cnt] = u;
	label[cnt] = cnt;
	sdom[cnt] = cnt;
	dsu[cnt] = cnt;
	for(auto e : adj[u]) {
		if(!arr[e]) {
			dfs(e);
			par[arr[e]] = arr[u];
		}
		radj[arr[e]].push_back(arr[u]);
	}
}

int find(int u, int x = 0) {
	if(u == dsu[u]) {
		return (x ? -1 : u);
	}
	int v = find(dsu[u], x + 1);
	if(v == -1) {
		return u;
	}
	if(sdom[label[dsu[u]]] < sdom[label[u]]) {
		label[u] = label[dsu[u]];
	}
	dsu[u] = v;
	return (x ? v : label[u]);
}

void unite(int u, int v) {
	dsu[v] = u;
}

// in main

dfs(1);
for(int i = cnt; i >= 1; i--) {
	for(auto e : radj[i]) {
		sdom[i] = min(sdom[i], sdom[find(e)]);
	}
	if(i > 1) {
		bucket[sdom[i]].push_back(i);
	}
	for(auto e : bucket[i]) {
		int v = find(e);
		if(sdom[e] == sdom[v]) {
			dom[e] = sdom[e];
		} else {
			dom[e] = v;
		}
	}
	if(i > 1) {
		unite(par[i], i);
	}
}
for(int i = 2; i <= cnt; i++) {
	if(dom[i] != sdom[i]) {
		dom[i] = dom[dom[i]];
	}
	tree[rev[i]].push_back(rev[dom[i]]);
	tree[rev[dom[i]]].push_back(rev[i]);
}
