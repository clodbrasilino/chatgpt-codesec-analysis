#include <stdio.h>
#include <stdlib.h>

void combinationUtil(int arr[], int n, int r, int index, int data[], int i) {
  if (index == r) {
    for (int j = 0; j < r; j++) {
      printf("%d ", data[j]);
    }
    printf("\n");
    return;
  }

  if (i >= n) return;

  data[index] = arr[i];
  combinationUtil(arr, n, r, index + 1, data, i + 1);
  combinationUtil(arr, n, r, index, data, i + 1);
}

void printCombinations(int arr[], int n) {
  for (int r = 1; r <= n; r++) {
    int data[r];
    combinationUtil(arr, n, r, 0, data, 0);
  }
}

int main() {
  int arr[] = {1, 2, 3};
  int n = sizeof(arr) / sizeof(arr[0]);
  printCombinations(arr, n);
  return 0;
}