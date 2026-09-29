#include <stdio.h>
#include <stdlib.h>

#define MAX 10

void countingSort(int array[], int size, int place) {
  int i;
  int output[size];
  int max = (array[0] / place) % MAX;

  for (i = 1; i < size; i++) {
    if (((array[i] / place) % MAX) > max) {
      max = array[i];
    }
  }

  int count[MAX];

  for (i = 0; i < MAX; ++i) {
    count[i] = 0;
  }

  for (i = 0; i < size; i++) {
    count[(array[i] / place) % MAX]++;
  }

  for (i = 1; i < MAX; ++i) {
    count[i] += count[i - 1];
  }

  for (i = size - 1; i >= 0; i--) {
    output[count[(array[i] / place) % MAX] - 1] = array[i];
    count[(array[i] / place) % MAX]--;
  }

  for (i = 0; i < size; i++) {
    array[i] = output[i];
  }
}

void radixsort(int array[], int size) {
  int max = array[0];
  int i;
  for (i = 1; i < size; i++) {
    if (array[i] > max) {
      max = array[i];
    }
  }

  for (int place = 1; max / place > 0; place *= 10) {
    countingSort(array, size, place);
  }
}

int main() {
  int array[] = {121, 432, 564, 23, 1, 45, 788};
  int n = sizeof(array) / sizeof(array[0]);
  radixsort(array, n);
  for (int i = 0; i < n; i++) {
    printf("%d ", array[i]);
  }
  return 0;
}