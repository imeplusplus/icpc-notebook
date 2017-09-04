int trie[N][26], trien = 1;
char p = 'a'; //a for lowercase, A for uppercase.

int add(int u, char c){
  if(trie[u][c-p]) return trie[u][c-p];
  return trie[u][c-p] = ++trien;
}

//to add a string s in the trie
int u = 1;
for(char c : s) u = add(u, c);
