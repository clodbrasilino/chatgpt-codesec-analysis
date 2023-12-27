#include <stdio.h>

int sublistMinLength(const int arr[], int n, int k) {
   int minLength = n + 1; 
   int start = 0, end = 0, sum = 0;
 
   while (end < n) {
       while (sum <= k && end < n) {
           sum += arr[end++];
       }
 
       while (sum > k && start < n) {
           if (end - start < minLength) {
               minLength = end - start;
           }
           sum -= arr[start++];
       }
   }
 
   return minLength;
}

int main() {
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int n = sizeof(arr) / sizeof(arr[0]);
  int k = 15;
  printf("Minimum length of sublist is %d\n", sublistMinLength(arr, n, k));
  return 0;
}