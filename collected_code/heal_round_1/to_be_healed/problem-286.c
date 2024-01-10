#include<stdio.h>

int findMaxContiguousSum(int arr[], int n, int k) {
   /* Possible weaknesses found:
    *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
    */
   int maxSum = arr[0];
   /* Possible weaknesses found:
    *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
    */
   int currentSum = arr[0];
   
   for(int i = 1; i < n * k; i++) {
      /* Possible weaknesses found:
       *  Cannot determine that 'arr[i%n]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
       */
      currentSum = currentSum + arr[i % n];
      if(currentSum > maxSum)
         maxSum = currentSum;
      if(currentSum < 0)
         currentSum = 0;
   }
   
   return maxSum;
}

int main() {
   int arr[] = {1, -2, 3, -4, 5, -6, 7, -8, 9, -10};
   int n = sizeof(arr) / sizeof(arr[0]);
   int k = 3;
   
   int largestSum = findMaxContiguousSum(arr, n, k);
   
   printf("Largest sum of contiguous subarray in modified array: %d\n", largestSum);
   
   return 0;
}