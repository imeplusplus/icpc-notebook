// Tarjan for SCC and Edge Biconnected Componentes - O(n + m)
vector<int> adj[N];
stack<int> st;
bool inSt[N];

int id[N], cmp[N];
int cnt, cmpCnt;

void clear(){
	memset(id, 0, sizeof id);
	cnt = cmpCnt = 0;
}

int tarjan(int n){
	int low;
	id[n] = low = ++cnt;
	st.push(n), inSt[n] = true;

	for(auto x : adj[n]){
		if(id[x] and inSt[x]) low = min(low, id[x]);
		else if(!id[x]) {
			int lowx = tarjan(x);
			if(inSt[x])
				low = min(low, lowx);
		}
	}

	if(low == id[n]){
		while(st.size()){
			int x = st.top();
			inSt[x] = false;
			cmp[x] = cmpCnt;

			st.pop();
			if(x == n) break;
		}
		cmpCnt++;
	}
	return low;
}
