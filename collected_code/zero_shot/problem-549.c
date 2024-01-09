#include <stdio.h>

int sumOfFifthPower(int n) {
   int sum = 0;
   int num = 1;

   for (int i = 1; i <= n; i++) {
      sum += num * num * num * num * num;
      num += 2;
   }

   return sum;
}

int main() {
   int n = 5;
   int result = sumOfFifthPower(n);

   printf("Sum of the fifth power of the first %d odd natural numbers: %d", n, result);

   return 0;
}