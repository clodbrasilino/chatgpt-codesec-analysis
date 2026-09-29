#include <stdio.h>

int calculateSum(int n) {
   int sum = 0;
   for(int i = 1; i <= n; i++) {
      sum += i * i * i;
   }
   return sum;
}

int main() {
   int n;
   printf("Enter the value of n: ");
   scanf("%d", &n);
   int sum = calculateSum(n);
   printf("The sum of the series is %d\n", sum);
   return 0;
}