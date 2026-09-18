#include<stdlib.h>
#include<stdio.h>

int PlatformsRequired(int arr[], int dep[], int n) {
   int plat_needed = 1, result = 1;
   int i = 1, j = 0;
 
   for (int i = 0; i < n; i++) {
      plat_needed = 1;
      for (int j = i + 1; j < n; j++) {
         if ((arr[i] >= arr[j] && arr[i] <= dep[j]) ||
            (arr[j] >= arr[i] && arr[j] <= dep[i]))
            plat_needed++;
      }
      result = (plat_needed > result) ? plat_needed : result;
    }
    return result;
}

int main() {
   int arr[] = {900, 940, 950, 1100, 1500, 1800};
   int dep[] = {910, 1200, 1120, 1130, 1900, 2000};
   int n = sizeof(arr) / sizeof(arr[0]);
   printf("Minimum Number of Platforms Required = %d", PlatformsRequired(arr, dep, n));
   return 0;
}