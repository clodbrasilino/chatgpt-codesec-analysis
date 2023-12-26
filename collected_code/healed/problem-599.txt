#include <stdio.h>

void sumAndAverage(int n) {
  int sum = 0;
  float average;

  for (int i = 1; i <= n; i++) {
    sum += i;
  }

  average = (float)sum / n;

  printf("Sum of first %d natural numbers is: %d\n", n, sum);
  printf("Average of first %d natural numbers is: %.2f\n", n, average);
}

int main() {
  int n = 0;

  printf("Enter the value of n: ");
  scanf("%d", &n);

  if (n > 0) {
    sumAndAverage(n);
  } else {
    printf("Invalid input. 'n' must be greater than 0.\n");
  }
  
  return 0;
}