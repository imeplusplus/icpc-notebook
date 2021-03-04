// @problem_url: https://codeforces.com/problemset/problem/340/D
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5;

int main() {
  int dp[N], v[N], n, lis;

  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> v[i];

  // @include: dynamic-programming/lis.cpp

  cout << lis << endl;
}
