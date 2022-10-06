/**********************************************************************************
* DIVIDE AND CONQUER OPTIMIZATION ( dp[i][k] = min j<k {dp[j][k-1] + C(j,i)} )    *
* Description: searches for bounds to optimal point using the monotocity condition*
* Condition: L[i][k] <= L[i+1][k]                                                 * 
* Time Complexity: O(K*N^2) becomes O(K*N*logN)                                   *                
* Notation: dp[i][k]: optimal solution using k positions, until position i        *
*           L[i][k]: optimal point, smallest j which minimizes dp[i][k]           *
*           C(i,j): cost for splitting range [j,i] to j and i                     *
**********************************************************************************/

const int N = 1e3+5;

ll dp[N][N];

//Cost for using i and j
ll C(ll i, ll j);

void compute(ll l, ll r, ll k, ll optl, ll optr){
    // stop condition  
    if(l > r) return;

    ll mid = (l+r)/2;
    //best : cost, pos
    pair<ll,ll> best = {LINF,-1};

    //searchs best: lower bound to right, upper bound to left
    for(ll i = optl; i <= min(mid, optr); i++){
        best = min(best, {dp[i][k-1] + C(i,mid), i});
    }
    dp[mid][k] = best.first;
    ll opt = best.second;

    compute(l, mid-1, k, optl, opt);
    compute(mid + 1, r, k, opt, optr);
}

//Iterate over k to calculate
ll solve(){
  //dimensions of dp[N][K]
  int n, k;

  //Initialize DP
  for(ll i = 1; i <= n; i++){
    //dp[i,1] = cost from 0 to i
    dp[i][1] = C(0, i);
  }

  for(ll l = 2; l <= k; l++){
    compute(1, n, l, 1, n);
  }

  /*+ Iterate over i to get min{dp[i][k]}, don't forget cost from n to i
    for(ll i=1;i<=n;i++){
        ll rest = ;
        ans = min(ans,dp[i][k] + rest);
    }
  */
}

