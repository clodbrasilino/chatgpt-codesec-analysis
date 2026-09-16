#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got 0
  *  test case 2 failed: expected 4, got 0
  *  test case 0 failed: expected 4, got 0
  */

int find_missing(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return -1;
    }

    if (arr[0] != 0) {
        return 0;
    }

    for (size_t i = 0; i < size; i++) {
        if (arr[i] != (int)i) {
            return (int)i;
        }
    }

    return (int)size;
}

int main(void) {
    int arr0[] = {0, 1, 2, 4, 5, 6};
    int missing0 = find_missing(arr0, sizeof(arr0) / sizeof(arr0[0]));
    printf("%d\n", missing0);

    int arr1[] = {1, 2, 3, 4, 5};
    int missing1 = find_missing(arr1, sizeof(arr1) / sizeof(arr1[0]));
    printf("%d\n", missing1);

    int arr2[] = {0, 1, 2, 3, 4};
    int missing2 = find_missing(arr2, sizeof(arr2) / sizeof(arr2[0]));
    printf("%d\n", missing2);

    int missing3 = find_missing(NULL, 0);
    printf("%d\n", missing3);

    return 0;
}