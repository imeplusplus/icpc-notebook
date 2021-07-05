// Kosaraju - SCC O(V+E)
// For undirected edges uncomment lines related to par, so after dfs it may know its route back through revdfs
vi adj[N], adjt[N];
int n, ordn, cnt, vis[N], ord[N], cmp[N];
// int par[N];

void dfs(int s){
    vis[s] = 1;
    for(auto v : adj[s]) if(!vis[v]) /*par[v] = s,*/ dfs(v);
    ord[ordn++] = s;
}

void revdfs(int s){
    vis[s] = 0;
    cmp[s] = cnt;
    for(auto v : adj[s]) if(vis[v] /*and s != par[v]*/) revdfs(v);
}

// in main
for (int i = 1; i <= n; ++i) if (!vis[i]) dfs(i);
for (int i = ordn-1; i >= 0; --i) if (vis[ord[i]]) cnt++, dfst(ord[i]);

/*Undirected SCC tested on Codeforces 1000E (Undirected SCC + diameter)*/