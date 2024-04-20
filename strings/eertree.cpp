// creates an automaton with the suffix links being the largest suffix palindrome of the current string, all on O(nlogalpha)

const int N = 1e6 + 7, alph = 26;
 
char s[N];
int len[N], link[N], to[alph][N], prv[N];
int n, last, sz;
long long ans;
 
void init() {
    s[n++] = -1;
    link[0] = 1;
    len[1] = -1;
    sz = 2;
}
 
int get_link(int v) {
    while(s[n - len[v] - 2] != s[n - 1]) v = link[v];
    return v;
}
 
void add_letter(char c) {
    s[n++] = c;
    last = get_link(last);
    if(!to[c - 'a'][last]) {
        len[sz] = len[last] + 2;
        link[sz] = to[c - 'a'][get_link(link[last])];
        to[c - 'a'][last] = sz++;
    }
    last = to[c - 'a'][last];
}
