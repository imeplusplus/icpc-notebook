// Extended Euclid: gcd(a, b) = x*a + y*b
void extgcd(int a, int b, int &x, int &y, int &d) {
  if (b) extgcd(b, a%b, y, x, d), y -= x*(a/b);
  else x = 1, y = 0, d = a;
}
