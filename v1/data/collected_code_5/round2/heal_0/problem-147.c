#include<stdio.h>
#include<stdlib.h>

#define MAX 100

int maxSum(int triangle[MAX][MAX], int m, int n) {
   if (n < 0 || n > m)
      return 0;
   else {
      int max_left = maxSum(triangle, m-1, n-1);
      int max_right = maxSum(triangle, m-1, n);
      int max_total = triangle[m][n] + (max_left > max_right ? max_left : max_right);
      return max_total;
   }
}

int main() {
   int triangle[MAX][MAX] = {
      {7, 0, 0, 0, 0},
      {3, 8, 0, 0, 0},
      {8, 1, 0, 0, 0},
      {2, 7, 4, 4, 0},
      {4, 5, 2, 6, 5}
   };
   int m = sizeof(triangle)/sizeof(triangle[0]);
   int n = sizeof(triangle[0])/sizeof(triangle[0][0]);
   int answer = maxSum(triangle, m-1, n-1);
   printf("The maximum total path sum is: %d", answer);
   return 0;
}