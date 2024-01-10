#include <stdio.h>

void moveZeroes(int arr[], int n) {
   int count = 0;

   for (int i = 0; i < n; i++) {
       /* Possible weaknesses found:
        *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
        */
       if (arr[i] != 0) {
           /* Possible weaknesses found:
            *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
            */
           arr[count] = arr[i];
           count++;
       }
   }

   while (count < n) {
       arr[count] = 0;
       count++;
   }
}

int main() {
   int arr[] = {6, 0, 8, 2, 3, 0, 4, 0, 1};
   int n = sizeof(arr) / sizeof(arr[0]);

   printf("Original Array: ");
   for (int i = 0; i < n; i++) {
       printf("%d ", arr[i]);
   }

   moveZeroes(arr, n);

   printf("\nModified Array: ");
   for (int i = 0; i < n; i++) {
       printf("%d ", arr[i]);
   }

   return 0;
}