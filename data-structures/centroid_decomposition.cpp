struct Centroid {
	vector<vector<int>> adj;
	vector<bool> vis;
	vector<int> par, sz;
	int n;
	Centroid(int n_) {
			n = n_;
			adj.resize(n + 1); vis.resize(n + 1);
			par.resize(n + 1); sz.resize(n + 1);
	}
	void add(int a, int b) {
			adj[a].push_back(b);
			adj[b].push_back(a);
	}
	int dfs_sz(int v, int p = -1) {
			if(vis[v]) {
					return 0;
			}
			sz[v] = 1;
			for(auto x : adj[v]) {
					if(x != p) {
							sz[v] += dfs_sz(x, v);
					}
			}
			return sz[v];
	}
	int centroid(int v, int p, int size) {
			for(auto x : adj[v]) {
					if(x != p and !vis[x] and sz[x] > size / 2) {
							return centroid(x, v, size);
					}
			}
			return v;
	}
	void gen_tree(int v = 1, int p = 0) {
			int c = centroid(v, v, dfs_sz(v));
			vis[c] = true;
			par[c] = p;
			for(auto x : adj[c]) {
					if(!vis[x]) {
							gen_tree(x, c);
					}
			}
			vis[c] = false;
	}
	void dfs(vector<int> &path, int i, int p = -1, int d = 0) {
			path.push_back(d);
			for(auto j : adj[i]) {
					if(j != p and !vis[j]) {
							dfs(path, j, i, d + 1);
					}
			}
	}
	//count paths of size k in the tree
	//if you want upto k, just change cnt to be a Fenwick Tree
	long long decomp(int i, int k) {
			int c = centroid(i, i, dfs_sz(i));
			vis[c] = true;
			long long ans = 0;
			vector<int> cnt(sz[i]);
			cnt[0] = 1;
			for(auto j : adj[c]) {
					if(!vis[j]) {
							vector<int> path;
							dfs(path, j);
							for(int d : path) {
									if(0 <= k - d - 1 and k - d - 1 < sz[i]) {
											ans += cnt[k - d - 1];
									}
							}
							for(int d : path) {
									cnt[d + 1]++;
							}
					}
			}
			for(int j : adj[c]) {
					if(!vis[j]) {
							ans += decomp(j, k);
					}
			}
			vis[c] = false;
			return ans;
	}
};