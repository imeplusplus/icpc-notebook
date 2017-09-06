// Closest Pair of Points - O(nlogn)
point p[N];

ld closest_pair_util(point p[], int n) {
  if (n <= 3) {
    ld ans = p[0].dist(p[1]);
    for (int i = 0; i < n; i++) for (int j = i+1; j < n; j++)
      ans = min(ans, p[i].dist(p[j]));
    return ans;
  }

  int mid = n/2;
  point mp = p[mid];
  ld d = min(closest_pair_util(p, mid), closest_pair_util(p+mid, n-mid));

  point strip[n];
  int sz = 0;
  for (int i = 0; i < n; i++) if ((p[i].x - mp.x)*(p[i].x - mp.x) < d) strip[sz++] = p[i];

  sort(strip, strip+sz, [](point s, point t){ return s.y > t.y; });
  for (int i = 0; i < sz; i++) for (int j = i+1; j < sz and (strip[i].y - strip[j].y)*(strip[i].y - strip[j].y) < d; j++)
    d = min(d, strip[i].dist(strip[j]));

  return d;
}

ld closest_pair(point p[], int n) {
  sort(p, p+n, [](point s, point t){ return s.x < t.x; });
  return closest_pair_util(p, n);
}
