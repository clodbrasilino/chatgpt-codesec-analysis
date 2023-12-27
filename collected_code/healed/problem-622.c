#include <stdio.h>

float findMedian(const int array1[], const int array2[], int size) {
  int merged[size * 2];
  int i = 0, j = 0, k = 0;
  
  while (i < size && j < size) {
    if (array1[i] <= array2[j]) {
      merged[k++] = array1[i++];
    } else {
      merged[k++] = array2[j++];
    }
  }

  while (i < size) {
    merged[k++] = array1[i++];
  }

  while (j < size) {
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