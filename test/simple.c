#include <stdio.h>

int compute(int x, int y) {
  int result = x + y;
  int doubled = result * 2;
  printf("Result: %d\n", doubled);
  return doubled;
}

int main() {
  int a = 5;
  int b = 10;
  return compute(a, b);
}
