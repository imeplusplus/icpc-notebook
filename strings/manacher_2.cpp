// Mancher O(n)

vector<int> d1, d2;

// d1 -> odd : size = 2 * d1[i] - 1, palindrome from i - d1[i] + 1 to i + d1[i] - 1
// d2 -> even : size = 2 * d2[i], palindrome from i - d2[i] to i + d2[i] - 1

void manacher(string &s) {
    int n = s.size();
    d1.resize(n), d2.resize(n);
    for(int i = 0, l1 = 0, l2 = 0, r1 = -1, r2 = -1; i < n; i++) {
        if(i <= r1) {
            d1[i] = min(d1[r1 + l1 - i], r1 - i + 1);
        }
        if(i <= r2) {
            d2[i] = min(d2[r2 + l2 - i + 1], r2 - i + 1);
        }
        while(i - d1[i] >= 0 and i + d1[i] < n and s[i - d1[i]] == s[i + d1[i]]) {
            d1[i]++;
        }
        while(i - d2[i] - 1 >= 0 and i + d2[i] < n and s[i - d2[i] - 1] == s[i + d2[i]]) {
            d2[i]++;
        }
        if(i + d1[i] - 1 > r1) {
            l1 = i - d1[i] + 1;
            r1 = i + d1[i] - 1;
        }
        if(i + d2[i] - 1 > r2) {
            l2 = i - d2[i];
            r2 = i + d2[i] - 1;
        }
    }
}
