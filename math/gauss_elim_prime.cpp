for(int k = 0; k < m; k++) {
    int l = k;
    while(l < n and !v[l][k].x) l++;
    if(l == n) {
        v[n][k] = 1;
        l = n++;
    }
    swap(v[k], v[l]);
    mint t = v[k][k];
    for(int j = 0; j <= m; j++) {
        v[k][j] /= t;
    }
    for(int i = 0; i < n; i++) {
        if(i == k) continue;
        mint q = v[i][k];
        for(int j = 0; j <= m; j++) {
            v[i][j] -= v[k][j] * q;
        }
    }
}
for(int i = m; i < n; i++) {
    mint s = 0;
    for(int k = 0; k < m; k++) {
        s += v[i][k] * v[k][m];
    }
    if(s != v[i][m]) {
        cout << -1 << "\n";
        return 0;
    }
}
