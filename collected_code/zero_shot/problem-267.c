#include <stdio.h>

int sum_of_squares(int n) {
   int sum = 0;
   for (int i = 1; i <= n; i++) {
      int odd_number = 2 * i - 1;
      sum += odd_number * odd_number;
   }
   return sum;
}

int main() {
   int n;
   printf("Enter the value of n: ");
   scanf("%d", &n);
   printf("Sum of squares of first %d odd natural numbers: %d\n", n, sum_of_squares(n));
   return 0;
}