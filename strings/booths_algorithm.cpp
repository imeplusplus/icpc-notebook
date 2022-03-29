// Booth's Algorithm - Find the lexicographically least rotation of a string in O(n)

string least_rotation(string s) {
  s += s;
  vector<int> f((int)s.size(), -1);
  int k = 0;
  for (int j = 1; j < (int)s.size(); j++) {
    int i = f[j - k - 1];
    while (i != -1 and s[j] != s[k + i + 1]) {
      if (s[j] < s[k + i + 1]) k = j - i - 1;
      i = f[i];
    }

    if (s[j] != s[k + i + 1]) {
      if (s[j] < s[k]) k = j;
      f[j - k] = -1;
    } else f[j - k] = i + 1;
  }

  return s.substr(k, (int)s.size() / 2);
}
