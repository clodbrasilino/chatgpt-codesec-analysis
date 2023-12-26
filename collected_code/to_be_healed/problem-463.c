#include <stdio.h>

int maxProductSubarray(int arr[], int n) {
   int max_ending_here = 1;
   int min_ending_here = 1;
   int max_so_far = 1;
 
   for (int i = 0; i < n; i++) {
      /* Possible weaknesses found:
       *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
       */
      if (arr[i] > 0) {
         /* Possible weaknesses found:
          *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
          */
         max_ending_here = max_ending_here * arr[i];
         /* Possible weaknesses found:
          *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
          *  implicit declaration of function 'min' [-Wimplicit-function-declaration]
          */
         min_ending_here = min(min_ending_here * arr[i], 1);
      /* Possible weaknesses found:
       *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
       */
      } else if (arr[i] == 0) {
         max_ending_here = 1;
         min_ending_here = 1;
      } else {
         int temp = max_ending_here;
         /* Possible weaknesses found:
          *  implicit declaration of function 'max' [-Wimplicit-function-declaration]
          */
         max_ending_here = max(min_ending_here * arr[i], 1);
         min_ending_here = temp * arr[i];
      }
 
      if (max_so_far < max_ending_here) {
         max_so_far = max_ending_here;
      }
   }
 
   return max_so_far;
}

int main() {
   int arr[] = {2, -3, 1, -2, 0, 9, -4};
   int n = sizeof(arr)/sizeof(arr[0]);
   printf("Maximum product subarray is %d\n", maxProductSubarray(arr, n));
   return 0;
}