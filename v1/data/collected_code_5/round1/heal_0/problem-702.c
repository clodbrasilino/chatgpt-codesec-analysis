#include <stdio.h>
#include <stdlib.h>

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int minElementsToRemove(int arr[], int n, int k) {
   qsort(arr, n, sizeof(int), cmpfunc);
   
   int j = 0;
   int minElem = n;
   
   for (int i = 0; i < n; ++i) {
       while (j < n && arr[j] - arr[i] <= k) {
           ++j;
       }
       minElem = (minElem < (n - j + i)) ? minElem : (n - j + i);
   }
   
   return minElem;
}

int main() {
    int arr[] = {1, 3, 4, 9, 10, 11, 12, 17, 20};
    int k = 4;
    int n = sizeof(arr) / sizeof(arr[0]);
    int minRemovals = minElementsToRemove(arr, n, k);
    
    printf("Minimum number of elements to remove: %d\n", minRemovals);
    
    return 0;
}