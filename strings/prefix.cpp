void p_f(char *s, int *pi) {
    int n = strlen(s);
    for(int i = 2; i <= n; i++) {
        pi[i]=pi[i-1];
        while(pi[i]>0 and s[pi[i]]!=s[i])
            pi[i]=pi[pi[i]];
        if(s[pi[i]]==s[i-1])
            pi[i]++;
    }
}
