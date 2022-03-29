// multiplicative function calculator
// euler_phi and mobius are multiplicative
// if another f[N] needed just remove comments
// O(N)

bool p[N];
vector<ll> primes;
ll g[N];
// ll f[N];

void mfc(){
    // if g(1) != 1 than it's not multiplicative
    g[1] = 1;
    // f[1] = 1;
    primes.clear();
    primes.reserve(N / 10);
    for(ll i = 2; i < N; i++){
        if(!p[i]){
            primes.push_back(i);
            for(ll j = i; j < N; j *= i){
                g[j] = // g(p^k) you found
                // f[j] = f(p^k) you found
                p[j] = (j != i);
            }
        }
        for(ll j : primes){
            if(i * j >= N || i % j == 0)
                break;
            for(ll k = j; i * k < N; k *= j){
                g[i * k] = g[i] * g[k];
                // f[i * k] = f[i] * f[k];
                p[i * k] = true;
            }
        }
    }
}
