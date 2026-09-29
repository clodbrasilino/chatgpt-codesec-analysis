#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

int max_subarray_sum(const int *arr, size_t size, int *result) {
    if (arr == NULL || result == NULL || size == 0) {
        errno = EINVAL;
        return -1;
    }

    int max_so_far = arr[0];
    int max_ending_here = arr[0];

    for (size_t i = 1; i < size; i++) {
        if (max_ending_here > 0 && arr[i] > INT_MAX - max_ending_here) {
            errno = ERANGE;
            return -1;
        }
        if (max_ending_here < 0 && arr[i] < INT_MIN - max_ending_here) {
            errno = ERANGE;
            return -1;
        }

        int sum = max_ending_here + arr[i];
        max_ending_here = (arr[i] > sum) ? arr[i] : sum;

        if (max_ending_here > max_so_far) {
            max_so_far = max_ending_here;
        }
    }

    *result = max_so_far;
    return 0;
}

int main(void) {
    int arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int result;

    if (max_subarray_sum(arr, size, &result) == 0) {
        printf("Largest sum of contiguous subarray: %d\n", result);
    } else {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}