#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 3, got <no output>
  *  test case 0 failed: expected 3, got <no output>
  *  test case 2 failed: expected -1, got <no output>
  */

int findEquilibriumIndex(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return -1;
    }

    long long totalSum = 0;
    for (size_t i = 0; i < size; i++) {
        totalSum += arr[i];
    }

    long long leftSum = 0;
    for (size_t i = 0; i < size; i++) {
        long long rightSum = totalSum - leftSum - arr[i];
        if (leftSum == rightSum) {
            return (int)i;
        }
        leftSum += arr[i];
    }

    return -1;
}

int main(void) {
    int arr1[] = {-7, 1, 5, 2, -4, 3, 0};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", findEquilibriumIndex(arr1, size1));

    int arr2[] = {1, 2, 3};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", findEquilibriumIndex(arr2, size2));

    int arr3[] = {2, 3, -1, 8, 4};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", findEquilibriumIndex(arr3, size3));

    return EXIT_SUCCESS;
}