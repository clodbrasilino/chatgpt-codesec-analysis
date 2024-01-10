#include <stdio.h>

int findRemainder(const int arr[], int n, int size) {
  int remainder = 1;

  for (int i = 0; i < size; i++) {
    remainder = (remainder * arr[i] % n);
  }

  return remainder;
}

int main() {
  const int arr[] = {5, 7, 3, 4};
  int n = 10;
  int size = sizeof(arr) / sizeof(arr[0]);

  int remainder = findRemainder(arr, n, size);
  printf("Remainder: %d\n", remainder);

  return 0;
}