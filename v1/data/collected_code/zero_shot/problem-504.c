#include <stdio.h>

int findCubeSum(int n) {
   int sum = 0;
   for (int i = 1; i <= n; i++) {
      sum += i * i * i;
   }
   return sum;
}

int main() {
   int n;
   printf("Enter the value of n: ");
   scanf("%d", &n);
   int cubeSum = findCubeSum(n);
   printf("The cube sum of the first %d natural numbers is %d.\n", n, cubeSum);
   return 0;
}