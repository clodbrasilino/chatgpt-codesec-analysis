#include <stdio.h>

int newmanConway(int n) {
  if (n == 0 || n == 1) {
    return 1;
  } else {
    return newmanConway(newmanConway(n - 1)) + newmanConway(n - newmanConway(n - 1));
  }
}

int main() {
  int n;
  printf("Enter the value of n: ");
  scanf("%d", &n);
  printf("The %dth number in the Newman-Conway sequence is: %d\n", n, newmanConway(n));
  return 0;
}