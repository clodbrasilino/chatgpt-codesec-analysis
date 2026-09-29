#include<stdio.h>

int findMaxContiguousSum(int arr[], int n, int k) {
   int maxSum = arr[0];
   int currentSum = arr[0];
   
   for(int i = 1; i < n * k; i++) {
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