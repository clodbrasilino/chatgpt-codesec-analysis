#include <stdio.h>
#include <stdlib.h>

int cmpfunc(const void* a, const void* b) {
   return (*(int*)b - *(int*)a);
}

void getNLargestItems(const int arr[], int size, int n) {
   int* copy = (int*) calloc(size, sizeof(int));
   
   if(copy == NULL) {
      return;
   }

   for(int i = 0; i < size; i++) {
       copy[i] = arr[i];
   }

   qsort(copy, size, sizeof(int), cmpfunc);

   printf("The %d largest items from the dataset are: ", n);
   for(int i = 0; i < n; i++) {
      printf("%d ", copy[i]);
   }

   free(copy);
   copy = NULL;
}

int main() {
   int dataset[] = {5, 8, 2, 10, 3, 1};
   int datasetSize = sizeof(dataset) / sizeof(dataset[0]);
   int n = 3;

   getNLargestItems(dataset, datasetSize, n);

   return 0;
}