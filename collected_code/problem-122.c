#include <stdio.h>

int isSmart(int num) {
   int i, sum = 1;

   for(i = 2; i <= num/2; i++) {
      if(num % i == 0) {
         sum += i;
      }
   }

   if(sum == num) {
      return 1;
   } else {
      return 0;
   }
}

int findNthSmartNumber(int n) {
   int count = 0, num = 6;

   while(count < n) {
      if(isSmart(num)) {
         count++;
      }
      num++;
   }

   return num-1;
}

int main() {
   int n, nthSmartNumber;

   printf("Enter the value of n: ");
   scanf("%d", &n);

   nthSmartNumber = findNthSmartNumber(n);

   printf("The %dth smart number is: %d", n, nthSmartNumber);

   return 0;
}