// Imagine you have a tree with colored vertices, and you want to do some type of query on every subtree about the colors inside
// complexity: O(nlogn)

vector<int> adj[N], vec[N];
int sz[N], color[N], cnt[N];

void dfs_size(int v = 1, int p = 0) {
	sz[v] = 1;
	for (auto u : adj[v]) {
		if (u != p) {
			dfs_size(u, v);
			sz[v] += sz[u];
		}
	}
}

void dfs(int v = 1, int p = 0, bool keep = false) {
	int Max = -1, bigchild = -1;
	for (auto u : adj[v]) {
		if (u != p && Max < sz[u]) {
			Max = sz[u];
			bigchild = u;
		}
	}
	for (auto u : adj[v]) {
		if (u != p && u != bigchild) {
			dfs(u, v, 0);
		}
	}
	if (bigchild != -1) {
		dfs(bigchild, v, 1);
		swap(vec[v], vec[bigchild]);
	}
	vec[v].push_back(v);
	cnt[color[v]]++;
	for (auto u : adj[v]) {
		if (u != p && u != bigchild) {
			for (auto x : vec[u]) {
				cnt[color[x]]++;
				vec[v].push_back(x);
			}
		}
	}
	// now here you can do what the query wants
	// there are cnt[c] vertex in subtree v color with c
	if (keep == 0) {
		for (auto u : vec[v]) {
			cnt[color[u]]--;
		}
	}
}
