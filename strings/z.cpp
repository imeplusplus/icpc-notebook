void z_f(char *s, int *z) {
  int l=0,r=0, n=strlen(s);
  for(int i = 1; i<n; i++) {
    if(i <= r)
      z[i]=min(z[i-l],r-i+1);
    while(z[i]+i<n and s[z[i]+i]==s[z[i]])
      z[i]++;
    if(r<i+z[i]-1)
      l=i,r=i+z[i]-1;
  }
}
