#include<stdio.h>

int sumLists(int list1[], int list2[], int length) {
   int i, sum = 0;
   for (i = 0; i < length; i++) {
      /* Possible weaknesses found:
       *  Cannot determine that 'list2[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
       *  Cannot determine that 'list1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
       */
      sum += list1[i] + list2[i];
   }
   return sum;
}

int main() {
   int list1[] = {1, 2, 3, 4};
   int list2[] = {5, 6, 7, 8};
   int length = sizeof(list1) / sizeof(list1[0]);
   int sum = sumLists(list1, list2, length);
   printf("Sum of lists: %d\n", sum);
   return 0;
}