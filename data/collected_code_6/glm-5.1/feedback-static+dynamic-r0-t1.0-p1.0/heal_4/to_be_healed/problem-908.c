#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 0, got <no output>
  *  test case 0 failed: expected 3, got <no output>
  *  test case 1 failed: expected -1, got <no output>
  */

int find_fixed_point(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return -1;
    }

    size_t low = 0;
    size_t high = size - 1;

    while (low <= high) {
        size_t mid = low + (high - low) / 2;
        if (arr[mid] == (int)mid) {
            return (int)mid;
        } else if (arr[mid] < (int)mid) {
            low = mid + 1;
        } else {
            if (mid == 0) break;
            high = mid - 1;
        }
    }

    return -1;
}

int main(void) {
    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    size_t n = 0;
    if (scanf("%zu", &n) != 1 || n == 0) {
        return EXIT_FAILURE;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return EXIT_FAILURE;
        }
    }

    int result = find_fixed_point(arr, n);
    printf("%d\n", result);

    free(arr);
    return EXIT_SUCCESS;
}