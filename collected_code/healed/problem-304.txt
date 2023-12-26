#include <stdio.h>

int findElement(int arr[], int n, int rotations, int index) {
   int mod = rotations % n;
   if (index < 0 || index >= n || mod < 0) {
         return -1;
   }
   return arr[(index + mod) % n];
}

int main() {
   int arr[] = {1, 2, 3, 4, 5};
   int n = sizeof(arr) / sizeof(arr[0]);
   int rotations = 2;
   int index = 3;
   int result = findElement(arr, n, rotations, index);
   if(result != -1) {
       printf("Element at index %d after %d rotations: %d\n", index, rotations, result);
   } else {
       printf("Error occurred.\n");
   }
   return 0;
}