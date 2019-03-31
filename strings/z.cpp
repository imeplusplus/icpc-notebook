// Z-Function - O(n)

string s;
int z[N];

void zfunc(string s){
  for(int i = 1, l = 0, r = 0, n = s.size(); i < n; i++){
    if(i <= r) z[i] = min(z[i-l], r - i + 1);
    while(i + z[i] < n and s[z[i]] == s[z[i] + i]) z[i]++;
    if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
  }
}

