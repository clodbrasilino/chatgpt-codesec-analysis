#include <stdio.h>

void merge(int arr[], const int left, const int mid, const int right) {
  int i, j, k;
  const int n1 = mid - left + 1;
  const int n2 = right - mid;

  int L[n1], R[n2];

  for (i = 0; i < n1; i++)
    L[i] = arr[left + i];

  for (j = 0; j < n2; j++)
    R[j] = arr[mid + 1 + j];

  i = 0;
  j = 0;
  k = left;

  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}

void mergeSort(int arr[], const int left, const int right) {
  if (left < right) {
    const int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
  
    merge(arr, left, mid, right);
  }
}

void printArray(const int arr[], const int size) {
  int i;
  for (i = 0; i < size; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

int main() {
  int arr[] = {12, 11, 13, 5, 6, 7};
  const int arrSize = sizeof(arr) / sizeof(arr[0]);

  printf("Given array is \n");
  printArray(arr, arrSize);

  mergeSort(arr, 0, arrSize - 1);

  printf("\nSorted array is \n");
  printArray(arr, arrSize);
  
  return 0;
}