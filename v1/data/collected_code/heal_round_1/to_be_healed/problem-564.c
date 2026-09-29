#include <stdio.h>

int countUnequalPairs(int arr[], int size) {
   int count = 0;

   for (int i = 0; i < size; i++) {
      for (int j = i + 1; j < size; j++) {
         /* Possible weaknesses found:
          *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
          *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
          */
         if (arr[i] != arr[j]) {
            count++;
         }
      }
   }

   return count;
}

int main() {
   int arr[] = {1, 2, 3, 4, 5};
   int size = sizeof(arr) / sizeof(arr[0]);

   int unequalPairsCount = countUnequalPairs(arr, size);

   printf("Number of unequal pairs: %d\n", unequalPairsCount);

   return 0;
}