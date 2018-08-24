// Tarjan for SCC and Edge Biconnected Componentes - O(n + m)
vector<int> adj[N];
stack<int> st;
bool inSt[N];

int low[N], id[N], cmp[N];
int cnt, cmpCnt;

void tarjan(int n){
  id[n] = low[n] = ++cnt;
  st.push(n), inSt[n] = true;

  for(auto x : adj[n]){
    if(id[x] and inSt[x]) low[n] = min(low[n], id[x]);
    else if(!id[x]) {
      tarjan(x);
      if(inSt[x])
        low[n] = min(low[n], low[x]);
    }
  }

  if(low[n] == id[n]){
    while(st.size()){
      int x = st.top();
      inSt[x] = false;
      cmp[x] = cmpCnt;

      st.pop();
      if(x == n) break;
    }
    cmpCnt++;
  }
}
