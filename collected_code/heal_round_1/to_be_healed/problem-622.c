#include <stdio.h>


float findMedian(int array1[], int array2[], int size) {
  int merged[size * 2];
  int i = 0, j = 0, k = 0;
  
  while (i < size && j < size) {
    /* Possible weaknesses found:
     *  Cannot determine that 'array2[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  Cannot determine that 'array1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    if (array1[i] <= array2[j]) {
      /* Possible weaknesses found:
       *  Cannot determine that 'array1[i++]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
       */
      merged[k++] = array1[i++];
    } else {
      /* Possible weaknesses found:
       *  Cannot determine that 'array2[j++]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
       */
      merged[k++] = array2[j++];
    }
  }
  
  while (i < size) {
    /* Possible weaknesses found:
     *  Cannot determine that 'array1[i++]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    merged[k++] = array1[i++];
  }
  
  while (j < size) {
    /* Possible weaknesses found:
     *  Cannot determine that 'array2[j++]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    merged[k++] = array2[j++];
  }
  
  float median;
  if (size % 2 == 0) {
    median = (merged[size - 1] + merged[size]) / 2.0;
  } else {
    median = merged[size - 1];
  }
  
  return median;
}


int main() {
  int array1[] = {1, 2, 3, 4, 5};
  int array2[] = {6, 7, 8, 9, 10};
  int size = sizeof(array1) / sizeof(array1[0]);
  
  float median = findMedian(array1, array2, size);
  
  printf("Median: %.2f\n", median);
  
  return 0;
}