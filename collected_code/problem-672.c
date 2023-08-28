#include <stdio.h>

int findMaximum(int a, int b, int c) {
   int max = a;
   
   if (b > max) {
      max = b;
   }
   
   if (c > max) {
      max = c;
   }
   
   return max;
}

int main() {
   int num1, num2, num3;

   printf("Enter three numbers: ");
   scanf("%d %d %d", &num1, &num2, &num3);

   int maximum = findMaximum(num1, num2, num3);

   printf("Maximum number is %d\n", maximum);

   return 0;
}