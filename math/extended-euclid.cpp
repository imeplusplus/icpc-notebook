// Extended Euclid
int x, y, d;
void extgcd(int a, int b) {
  if (!b) { x = 1; y = 0; d = a; return; }
  extgcd(b, a%b);
  int x1 = y, y1 = x-(a/b)*y;
  x = x1, y = y1;
}
