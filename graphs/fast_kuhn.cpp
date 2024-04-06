const int N = 1e5+5;

int x, marcB[N], matchB[N], matchA[N], ans, n, m, p;
vector<int> adj[N];

bool dfs(int v){
	for(int i = 0; i < adj[v].size(); i++){
		int viz = adj[v][i];
		if(marcB[viz] == 1 ) continue;
		marcB[viz] = 1;

		if((matchB[viz] == -1) || dfs(matchB[viz])){
			matchB[viz] = v;
			matchA[v] = viz;
			return true;
		}
	
	}
	return false;
}

int main(){
	//...
	for(int i = 0; i<=n; i++) matchA[i] = -1;
	for(int j = 0; j<=m; j++) matchB[j] = -1;

	bool aux = true;
	while(aux){
		for(int j=1; j<=m; j++) marcB[j] = 0;
		aux = false;
		for(int i=1; i<=n; i++){
			if(matchA[i] != -1) continue;
			if(dfs(i)){
				ans++;
				aux = true;
			}
		}
	}
	//...
}
