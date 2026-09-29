#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
  int t = *a;
  *a = *b;
  *b = t;
}

void selectionSort(int arr[], int n) {
  int i, j, min_idx;

  for (i = 0; i < n-1; i++) {
    min_idx = i;
    for (j = i+1; j < n; j++)
      if (arr[j] < arr[min_idx])
        min_idx = j;

    swap(&arr[min_idx], &arr[i]);
  }
}

int* getSmallestN(int* arr, int size, int n) {
  if (arr == NULL || size < n || n < 0) {
    return NULL;
  }

  selectionSort(arr, size);
  int* result = (int*) malloc(sizeof(int) * n);

  if (result != NULL) {
    for (int i = 0; i < n; i++) {
      result[i] = arr[i];
    }
  }

  return result;
}

int main() {
  int arr[] = {12, 11, 13, 5, 6, 7};
  int size = sizeof(arr)/sizeof(arr[0]);

  int n;
  printf("Enter the number of smallest items to get: ");
  scanf("%d", &n);

  int* smallestN = getSmallestN(arr, size, n);

  if(smallestN != NULL) {
    printf("The smallest %d items are: ", n);
    for (int i = 0; i < n; i++) {
      printf("%d ", smallestN[i]);
    }
    free(smallestN);
  } else {
    printf("Invalid operation.\n");
  }
   
  return 0;
}