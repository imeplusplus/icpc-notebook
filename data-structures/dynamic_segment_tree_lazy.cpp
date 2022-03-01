#include <bits/stdc++.h>

/* tested:
    https://www.spoj.com/problems/BGSHOOT/
   ref:
    https://maratona.ic.unicamp.br/MaratonaVerao2022/slides/AulaSummer-SegmentTree-Aula2.pdf
*/
vector<int> e, d, mx, lazy;
//begin creating node 0, then start your segment tree creating node 1
int create(){
    mx.push_back(0);
    lazy.push_back(0);
    e.push_back(0);
    d.push_back(0);
    return mx.size() - 1;
}

void push(int pos, int ini, int fim){
    if(pos == 0) return;
    if (lazy[pos]) {
        mx[pos] += lazy[pos];
        // RMQ (max/min)   -> update: = lazy[p],         incr: += lazy[p]
        // RSQ (sum)       -> update: = (r-l+1)*lazy[p], incr: += (r-l+1)*lazy[p]
        // Count lights on -> flip:   = (r-l+1)-st[p];
        if (ini != fim) {
            if(e[pos] == 0){
                int aux = create();
                e[pos] = aux;
            }
            if(d[pos] == 0){
                int aux = create();
                d[pos] = aux;
            }
            lazy[e[pos]] += lazy[pos];
            lazy[d[pos]] += lazy[pos];
            // update:    lazy[2*p] = lazy[p],  lazy[2*p+1] = lazy[p];
            // increment: lazy[2*p] += lazy[p], lazy[2*p+1] += lazy[p];
            // flip:      lazy[2*p] ^= 1,       lazy[2*p+1] ^= 1;
        }
        lazy[pos] = 0;
    }
}

void update(int pos, int ini, int fim, int p, int q, int val){
    if(pos == 0) return;

    push(pos, ini, fim);

    if(q < ini || p > fim) return;

    if(p <= ini and fim <= q){
        lazy[pos] += val;
        // update:    lazy[p] = k;
        // increment: lazy[p] += k;
        // flip:      lazy[p] = 1;
        push(pos, ini, fim);
        return;
    }

    int m = (ini + fim) >> 1;
    if(e[pos] == 0){
        int aux = create();
        e[pos] = aux;
    }
    update(e[pos], ini, m, p, q, val);
    if(d[pos] == 0){
        int aux = create();
        d[pos] = aux;
    }
    update(d[pos], m + 1, fim, p, q, val);
    mx[pos] = max(mx[e[pos]], mx[d[pos]]);
}

int query(int pos, int ini, int fim, int p, int q){
    if(pos == 0) return 0;

    push(pos, ini, fim);

    if(q < ini || p > fim) return 0;

    if(p <= ini and fim <= q) return mx[pos];
    
    int m = (ini + fim) >> 1;
    return max(query(e[pos], ini, m, p, q) , query(d[pos], m + 1, fim, p, q));
}