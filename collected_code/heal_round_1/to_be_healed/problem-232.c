#include <stdio.h>
#include <stdlib.h>

int cmpfunc(const void* a, const void* b) {
   /* Possible weaknesses found:
    *  Cannot determine that '*(int*)b' is initialized [premium-bughuntingUninit]
    *  Cannot determine that '*(int*)a' is initialized [premium-bughuntingUninit]
    */
   return (*(int*)b - *(int*)a);
}

void getNLargestItems(int arr[], int size, int n) {
   /* Possible weaknesses found:
    *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
    */
   qsort(arr, size, sizeof(int), cmpfunc);
   
   printf("The %d largest items from the dataset are: ", n);
   for(int i = 0; i < n; i++) {
      printf("%d ", arr[i]);
   }
}

int main() {
   int dataset[] = {5, 8, 2, 10, 3, 1};
   int datasetSize = sizeof(dataset) / sizeof(dataset[0]);
   int n = 3;
   
   getNLargestItems(dataset, datasetSize, n);
   
   return 0;
}