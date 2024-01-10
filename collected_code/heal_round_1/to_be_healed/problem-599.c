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
  int n;
  printf("Enter the value of n: ");
  /* Possible weaknesses found:
   *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
   */
  scanf("%d", &n);
  
  sumAndAverage(n);
  
  return 0;
}