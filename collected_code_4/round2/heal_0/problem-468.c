#include <stdio.h>
#include <stdlib.h>

int maxProductSubsequence(int arr[], int n) {
  int maxProduct = 1;
  int currProduct = 1;
  int i, j;

  for (i = 0; i < n; ++i) {
    currProduct = arr[i];
    for (j = i + 1; j < n; ++j) {
      if (arr[j] > arr[j - 1])
        currProduct *= arr[j];
      else
        break;
    }

    if (currProduct > maxProduct)
      maxProduct = currProduct;
  }

  return maxProduct;
}

int main() {
  int n;
  printf("Enter the size of the array: ");
  scanf("%d", &n);

  int* arr = (int*)malloc(n * sizeof(int));
  if (!arr) {
    printf("Memory allocation failed!\n");
    return 0;
  }

  printf("Enter elements of array:\n");
  for (int i = 0; i < n; ++i) {
    scanf("%d", &arr[i]);
  }

  int maxProduct = maxProductSubsequence(arr, n);
  printf("Maximum product subsequence is %d\n", maxProduct);

  free(arr);

  return 0;
}

