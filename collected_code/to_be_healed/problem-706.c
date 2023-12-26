#include <stdio.h>

// Function to check if array2 is a subset of array1
int isSubset(int array1[], int array2[], int m, int n) {
   int i = 0, j = 0;

   // Traverse both arrays
   for (i = 0; i < n; i++) {
      for (j = 0; j < m; j++) {
         /* Possible weaknesses found:
          *  Cannot determine that 'array2[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
          *  Cannot determine that 'array1[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
          */
         if(array2[i] == array1[j])
            break;
      }
      
      // If the element is not found in array1
      if (j == m)
         return 0;
   }
   
   // If all elements are found
   return 1;
}

int main() {
   int array1[] = {4, 7, 2, 9, 11, 6};
   int array2[] = {5, 4, 2};

   int m = sizeof(array1)/sizeof(array1[0]);
   int n = sizeof(array2)/sizeof(array2[0]);

   if (isSubset(array1, array2, m, n))
      printf("array2[] is a subset of array1[]");
   else
      printf("array2[] is not a subset of array1[]");

   return 0;
}