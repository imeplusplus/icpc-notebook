//amortized O(logn) for every operation

using namespace std;

namespace allocat {
    template<class T, int MAXSIZE> struct array {
        T v[MAXSIZE], *top;
        array() : top(v) {}
        T *alloc(const T &val = T()) {
            return &(*top++ = val);
        }
        void dealloc(T *p) {}
    };
    template<class T, int MAXSIZE> struct stack {
        T v[MAXSIZE], *spot[MAXSIZE], **top;
        stack() {
            for(int i = 0; i < MAXSIZE; i++) {
                spot[i] = v + i;
            }
            top = spot + MAXSIZE;
        }
        T *alloc(const T &val = T()) {
            return &(**--top = val);
        }
        void dealloc(T *p) {
            *top++ = p; 
        }
    };
}

namespace splay {
    template<class T> struct node {
        T *f, *c[2];
        int size;
        node() {
            f = c[0] = c[1] = nullptr;
            size = 1;
        }
        void push_down() {}
        void update() {
            size = 1;
            for(int t = 0; t < 2; t++) {
                if(c[t]) {
                    size += c[t]->size;
                }
            }
        }
    };
    template<class T> struct reversible_node : node<T> {
        int r;
        reversible_node() : node<T>() {
            r = 0;
        }
        void push_down() {
            node<T>::push_down();
            if(r) {
                for(int t = 0; t < 2; t++) {
                    if(node<T>::c[t]) {
                        node<T>::c[t]->reverse();
                    }
                    r = 0;
                }
            }
        }
        void update() {
            node<T>::update();
        }
        void reverse() {
            swap(node<T>::c[0], node<T>::c[1]);
            r = r ^ 1;
        }
    };
    template<class T, int MAXSIZE = (int)5e5, class alloc = allocat::array<T, MAXSIZE + 2>> struct tree {
        alloc pool;
        T *root;
        T *new_node(const T &val = T()) {
            return pool.alloc(val);
        }
        tree() {
            root = new_node();
            root->c[1] = new_node();
            root->size = 2;
            root->c[1]->f = root;
        }
        void rotate(T *n) {
            int v = n->f->c[0] == n;
            T *p = n->f, *m = n->c[v];
            if(p->f) {
                p->f->c[p->f->c[1] == p] = n;
            }
            n->f = p->f;
            n->c[v] = p;
            p->f = n;
            p->c[v ^ 1] = m;
            if(m) {
                m->f = p;
            }
            p->update();
            n->update();
        }
        void splay(T *n, T *s = nullptr) {
            while(n->f != s) {
                T *m = n->f, *l = m->f;
                if(l == s) {
                    rotate(n);
                } else if((l->c[0] == m) == (m->c[0] == n)) {
                    rotate(m);
                    rotate(n);
                } else {
                    rotate(n);
                    rotate(n);
                }
            }
            if(!s) {
                root = n;
            }
        }
        int size() {
            return root->size - 2;
        }
        int walk(T *n, int &v, int &pos) {
            n->push_down();
            int s = n->c[0] ? n->c[0]->size : 0;
            (v = s < pos) && (pos -= s + 1);
            return s;
        }
        void insert(T *n, int pos) {
            T *c = root;
            int v;
            pos++;
            while(walk(c, v, pos), c->c[v] and (c = c->c[v]));
            c->c[v] = n;
            n->f = c;
            splay(n);
        }
        T *find(int pos, int sp = true) {
            T *c = root;
            int v;
            pos++;
            while((pos < walk(c, v, pos) or v) and (c = c->c[v]));
            if(sp) {
                splay(c);
            }
            return c;
        }
        T *find_range(int posl, int posr) {
            T *r = find(posr), *l = find(posl - 1, false);
            splay(l, r);
            if(l->c[1]) {
                l->c[1]->push_down();
            }
            return l->c[1];
        }
        void insert_range(T **nn, int nn_size, int pos) {
            T *r = find(pos), *l = find(pos - 1, false), *c = l;
            splay(l, r);
            for(int i = 0; i < nn_size; i++) {
                c->c[1] = nn[i];
                nn[i]->f = c;
                c = nn[i];
            }
            for(int i = nn_size - 1; i >= 0; i--) {
                nn[i]->update();
            }
            l->update(), r->update(), splay(nn[nn_size - 1]);
        }
        void dealloc(T *n) {
            if(!n) {
                return;
            }
            dealloc(n->c[0]);
            dealloc(n->c[1]);
            pool.dealloc(n);
        }
        void erase_range(int posl, int posr) {
            T *n = find_range(posl, posr);
            n->f->c[1] = nullptr, n->f->update(), n->f->f->update(), n->f = nullptr;
            dealloc(n);
        }
    };
}

struct node: splay::reversible_node<node> {
    long long val, val_min, lazy;
    node(long long v = 0) : splay::reversible_node<node>(), val(v) {
        val_min = lazy = 0;
    }
    void add(long long v) {
        val += v;
        val_min += v;
        lazy += v;
    }
    void push_down() {
        splay::reversible_node<node>::push_down();
        for(int t = 0; t < 2; t++) {
            if(c[t]) {
                c[t]->add(lazy);
            }
        }
        lazy = 0;
    }
    void update() {
        splay::reversible_node<node>::update();
        val_min = val;
        for(int t = 0; t < 2; t++) {
            if(c[t]) {
                val_min = min(val_min, c[t]->val_min);
            }
        }
    }
};

const int N = 2e5 + 7;
splay::tree<node, N, allocat::stack<node, N + 2>> t;

// in main

// to insert:
t.insert(t.new_node(node(x)), t.size());

//adding a certain value to a certain range
t.find_range(x - 1, y)->add(d);

//reversing a certain range
t.find_range(x - 1, y)->reverse();

//cycling to the right a certain range
d %= (y - x + 1);
if(d) {
  node *right = t.find_range(y - d, y);
  right->f->c[1] = nullptr, right->f->update(), right->f->f->update(), right->f = nullptr;
  t.insert(right, x - 1);
}

//inserting value p at position x + 1
t.insert(t.new_node(node(p)), x);

//deleting a certain value/range
t.erase_range(x - 1, y);

//getting the minimum of a certain range (change this accordingly)
t.find_range(x - 1, y)->val_min 
