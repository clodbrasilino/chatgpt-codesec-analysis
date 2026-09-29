#include <stdio.h>

int findElement(int arr[], int n, int rotations, int index) {
   int mod = rotations % n;
   /* Possible weaknesses found:
    *  Cannot determine that 'arr[(index+mod)%n]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
    */
   return arr[(index + mod) % n];
}

int main() {
   int arr[] = {1, 2, 3, 4, 5};
   int n = sizeof(arr) / sizeof(arr[0]);
   int rotations = 2;
   int index = 3;
   int result = findElement(arr, n, rotations, index);
   printf("Element at index %d after %d rotations: %d\n", index, rotations, result);
   return 0;
}