#include<stdio.h>

int findFrequency(int arr[], int size, int num) {
   int count = 0;
   for (int i = 0; i < size; i++) {
      /* Possible weaknesses found:
       *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
       */
      if (arr[i] == num) {
         count++;
      }
   }
   return count;
}

int main() {
   int arr[] = {1, 2, 3, 4, 5, 2, 3, 2, 4, 2};
   int size = sizeof(arr) / sizeof(arr[0]);
   int num = 2;
   
   int frequency = findFrequency(arr, size, num);
   printf("Frequency of %d in the array is %d\n", num, frequency);
   
   return 0;
}