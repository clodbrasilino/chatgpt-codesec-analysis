#include <stdio.h>

int findNthStarNumber(int n) {
   int starNum = 1;
   
   for(int i = 1; i <= n; i++) {
       starNum = 2 * starNum + 1;
   }
   
   return starNum;
}

int main() {
   int n = 5;
   int nthStarNumber = findNthStarNumber(n);
   printf("The %dth star number is %d\n", n, nthStarNumber);
   
   return 0;
}