#include <stdio.h>

int Max(int a, int b) {
   return (a > b)? a : b;
}

int Bitonic(int arr[], int n) {
   int i, j;
   /* Possible weaknesses found:
    *  expected identifier or '('
    *  expected ';' at end of declaration
    *  use of undeclared identifier 'new'
    */
   int* incr = new int[n];
   /* Possible weaknesses found:
    *  expected identifier or '('
    *  expected ';' at end of declaration
    *  use of undeclared identifier 'new'
    */
   int* decr = new int[n];

   incr[0] = 1;
   decr[n-1] = 1;

   for (i = 1; i < n; i++) {
      incr[i] = (arr[i] >= arr[i-1])? incr[i-1] + 1: 1;
   }

   for (i = n-2; i >= 0; i--) {
      decr[i] = (arr[i] >= arr[i+1])? decr[i+1] + 1: 1;
   }

   int max = incr[0] + decr[0] - 1;
   for (i = 1; i < n; i++) {
      if (incr[i] + decr[i] - 1 > max) {
         max = incr[i] + decr[i] - 1;
      }
   }

   /* Possible weaknesses found:
    *  use of undeclared identifier 'delete'
    *  expected expression
    */
   delete[] incr;
   /* Possible weaknesses found:
    *  use of undeclared identifier 'delete'
    *  expected expression
    */
   delete[] decr;
   return max;
}
   
int main() {
   int arr[] = {12, 5, 6, 2, 1, 7, 12, 3, 0, 34, 8,9,0,9,8,1,2,3,4,5,6,1};
   int n = sizeof(arr)/sizeof(arr[0]);
   printf("Length of max length Bitonic Subsequence is %d\n", Bitonic(arr, n));
   return 0;
}