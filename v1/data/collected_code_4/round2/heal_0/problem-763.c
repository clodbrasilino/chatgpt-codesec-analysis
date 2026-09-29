#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int findMinDifference(int arr[], int n) {
  int minDiff = INT_MAX;
  for (int i = 0; i < n-1; i++) {
    for (int j = i+1; j < n; j++) {
      if (abs(arr[i] - arr[j]) < minDiff) {
        minDiff = abs(arr[i] - arr[j]);
      }
    }
  }
  return minDiff;
}

int main() {
  int arr[] = {2, 3, 11, 6, 5, 9};
  int n = sizeof(arr)/sizeof(arr[0]);
  printf("Minimum difference is %d ", findMinDifference(arr, n));
  return 0;
}