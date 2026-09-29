#include <stdio.h>

int findRemainder(int arr[], int n, int size) {
  int remainder = 1;

  for (int i = 0; i < size; i++) {
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    remainder = (remainder * arr[i] % n);
  }

  return remainder;
}

int main() {
  int arr[] = {5, 7, 3, 4};
  int n = 10;
  int size = sizeof(arr) / sizeof(arr[0]);

  int remainder = findRemainder(arr, n, size);
  printf("Remainder: %d\n", remainder);

  return 0;
}