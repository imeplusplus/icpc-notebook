void p_f(char *s, int *pi) {
    int n = strlen(s);
    pi[0]=pi[1]=0;
    for(int i = 2; i <= n; i++) {
        pi[i] = pi[i-1];
        while(pi[i]>0 and s[pi[i]]!=s[i])
            pi[i]=pi[pi[i]];
        if(s[pi[i]]==s[i-1])
            pi[i]++;
    }
}

int main() {
    //...
    //Initialize prefix function
    char p[N]; //Pattern
    int len = strlen(p); //Pattern size
    int pi[N]; //Prefix function
    p_f(p, pi);

    // Create KMP automaton
    int A[N][128]; //A[i][j]: from state i (size of largest suffix of text which is prefix of pattern), append character j -> new state A[i][j]
    for( char c : ALPHABET )
        A[0][c] = (p[0] == c);
    for( int i = 1; p[i]; i++ ) {
        for( char c : ALPHABET ) {
            if(c==p[i])
                A[i][c]=i+1; //match
            else
                A[i][c]=A[pi[i]][c]; //try second largest suffix
        }
    }

    //Create KMP "string appending" automaton
    // g_n = g_(n-1) + char(n) + g_(n-1)
    // g_0 = "", g_1 = "a", g_2 = "aba", g_3 = "abacaba", ...
    int F[M][N]; //F[i][j]: from state j (size of largest suffix of text which is prefix of pattern), append string g_i -> new state F[i][j]
    for(int i = 0; i < m; i++) {
        for(int j = 0; j <= len; j++) {
            if(i==0)
                F[i][j] = j; //append empty string
            else {
                int x = F[i-1][j]; //append g_(i-1)
                x = A[x][j]; //append character j
                x = F[i-1][x]; //append g_(i-1)
                F[i][j] = x;
            }
        }
    }

    //Create number of matches matrix
    int K[M][N]; //K[i][j]: from state j (size of largest suffix of text which is prefix of pattern), append string g_i -> K[i][j] matches
    for(int i = 0; i < m; i++) {
        for(int j = 0; j <= len; j++) {
            if(i==0)
                K[i][j] = (j==len); //append empty string
            else {
                int x = F[i-1][j]; //append g_(i-1)
                x = A[x][j]; //append character j

                K[i][j] = K[i-1][j] /*append g_(i-1)*/ + (x==len) /*append character j*/ + K[i-1][x]; /*append g_(i-1)*/
            }
        }
    }
    //number of matches in g_k
    int answer = K[0][k];
    //...
}

