#include <stdio.h>

int findCubeSum(int n) {
   int sum = 0;
   for (int i = 1; i <= n; i++) {
      sum += i * i * i;
   }
   return sum;
}

int main() {
   int n = 0;
   printf("Enter the value of n: ");
   scanf("%d", &n);
   if (n > 0) {
       int cubeSum = findCubeSum(n);
       printf("The cube sum of the first %d natural numbers is %d.\n", n, cubeSum);
    } else {
       printf("Invalid input. Please enter a natural number.\n");
    }
   return 0;
}