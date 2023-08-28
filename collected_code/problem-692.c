#include <stdio.h>

int lastTwoDigitsFactorial(int n) {
  int fact = 1;
  for (int i = 1; i <= n; i++) {
    fact *= i;
    fact %= 100;
  }
  return fact;
}

int main() {
  int num;
  printf("Enter a number: ");
  scanf("%d", &num);
  int result = lastTwoDigitsFactorial(num);
  printf("Last two digits of factorial of %d is: %02d\n", num, result);
  return 0;
}