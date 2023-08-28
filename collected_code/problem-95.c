#include <stdio.h>

int sublistMinLength(int arr[], int n, int k) {
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