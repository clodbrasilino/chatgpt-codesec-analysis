#include<stdio.h>

void packDuplicates(int arr[], int size) {
   int i, j;
   printf("[");
   for(i = 0; i < size; i++) {
      if(i > 0 && arr[i] != arr[i-1])
         printf("]");
      if(i == 0 || arr[i] != arr[i-1]) {
         printf("[");
      }
      printf("%d", arr[i]);
   }
   printf("]");
}

int main() {
   int arr[] = {1, 1, 2, 2, 2, 3, 4, 4, 5};
   int size = sizeof(arr) / sizeof(arr[0]);
   packDuplicates(arr, size);
   return 0;
}