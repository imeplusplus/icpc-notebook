// 2-SAT - O(V+E)
// For each variable x, we create two nodes in the graph: u and !u
// If the variable has index i, the index of u and !u are: 2*i and 2*i+1
// Adds a statment u => v
void add(int u, int v){
	adj[u].pb(v);
	adj[v^1].pb(u^1);
}

//0-indexed variables; starts from var_0 and goes to var_n-1
for(int i = 0; i < n; i++){
	tarjan(2*i), tarjan(2*i + 1);
	//cmp is a tarjan variable that says the component from a certain node
	if(cmp[2*i] == cmp[2*i + 1]) //Invalid
	if(cmp[2*i] < cmp[2*i + 1]) //Var_i is true
	else //Var_i is false
		
	//its just a possible solution!
}
