/***********************************************************************************************
* 2-SAT (TELL WHETHER A SERIES OF STATEMENTS CAN OR CANNOT BE FEASIBLE AT THE SAME TIME)       *                                                                                   *
* Time complexity: O(V+E)                                                                      *
* Usage: n         -> number of variables, 1-indexed                                           *
*        p = v(i)  -> picks the "true" state for variable i                                    *
*        p = nv(i) -> picks the "false" state for variable i, i.e. ~i                          *
*        add(p, q) -> add clause (p v q) (which also means ~p => q, which also means ~q => p)  *
*        run2sat() -> true if possible, false if impossible                                    *
*        val[i]    -> tells if i has to be true or false for that solution                     *
***********************************************************************************************/

int n, vis[2*N], ord[2*N], ordn, cnt, cmp[2*N], val[N];
vector<int> adj[2*N], adjt[2*N];

// for a variable u with idx i
// u is 2*i and !u is 2*i+1
// (a v b) == !a -> b ^ !b -> a

int v(int x) { return 2*x; }
int nv(int x) { return 2*x+1; }

// add clause (a v b)
void add(int a, int b){
	adj[a^1].push_back(b);
	adj[b^1].push_back(a);
	adjt[b].push_back(a^1);
	adjt[a].push_back(b^1);
}

void dfs(int x){
	vis[x] = 1;
	for(auto v : adj[x]) if(!vis[v]) dfs(v);
	ord[ordn++] = x;
}

void dfst(int x){
	cmp[x] = cnt, vis[x] = 0;
	for(auto v : adjt[x]) if(vis[v]) dfst(v);
}

bool run2sat(){
	for(int i = 1; i <= n; i++) {
		if(!vis[v(i)]) dfs(v(i));
		if(!vis[nv(i)]) dfs(nv(i));
	}
	for(int i = ordn-1; i >= 0; i--) 
		if(vis[ord[i]]) cnt++, dfst(ord[i]);
	for(int i = 1; i <= n; i ++){
		if(cmp[v(i)] == cmp[nv(i)]) return false;
		val[i] = cmp[v(i)] > cmp[nv(i)];
	}
	return true;
}

int main () {
		for (int i = 1; i <= n; i++) {
				if (val[i]); // i-th variable is true
				else         // i-th variable is false
}
