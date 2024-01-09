#include <stdio.h>

int max(int num1, int num2) {
   return (num1 > num2) ? num1 : num2;
}

int main() {
   int a = 10;
   int b = 20;
   int result = max(a, b);
   printf("Maximum number is: %d", result);

   return 0;
}