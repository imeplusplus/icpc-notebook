int dp[N], v[N], n, lis;

memset(dp, 63, sizeof dp);
for(int i=0; i<n; ++i) {
  int j = lower_bound(dp, dp+lis, v[i]) - dp;
  dp[j] = min(dp[j], v[i]);
  lis = max(lis, j+1);
}
