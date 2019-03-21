vector<int> ans, adj[N];
int in[N];

void dfs(int v){
  while(adj[v].size()){
    int x = adj[v].back();
    adj[v].pop_back();
    dfs(x);
  }
  ans.pb(v);
}

// Verify if there is an eulerian path or circuit
vector<int> v;
for(int i = 0; i < n; i++) if(adj[i].size() != in[i]){
  if(abs((int)adj[i].size() - in[i]) != 1) //-> There is no valid eulerian circuit/path
  v.pb(i);
}

if(v.size()){
  if(v.size() != 2) //-> There is no valid eulerian path
  if(in[v[0]] > adj[v[0]].size()) swap(v[0], v[1]);
  if(in[v[0]] > adj[v[0]].size()) //-> There is no valid eulerian path
  adj[v[1]].pb(v[0]); // Turn the eulerian path into a eulerian circuit
}

dfs(0);
for(int i = 0; i < cnt; i++)
  if(adj[i].size()) //-> There is no valid eulerian circuit/path in this case because the graph is not conected
  
ans.pop_back(); // Since it's a curcuit, the first and the last are repeated
reverse(ans.begin(), ans.end());

int bg = 0; // Is used to mark where the eulerian path begins
if(v.size()){
  for(int i = 0; i < ans.size(); i++)
    if(ans[i] == v[1] and ans[(i + 1)%ans.size()] == v[0]){
      bg = i + 1;
      break;
    }
}
