#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max_subarray_sum(const int *arr, size_t n, int *result)
{
    size_t i;
    long long current;
    long long best;

    if (arr == NULL || n == 0 || result == NULL) {
        return -1;
    }

    current = arr[0];
    best = arr[0];

    for (i = 1; i < n; i++) {
        /* Possible weaknesses found:
         *  Invalid test for overflow 'current+arr[i]>arr[i]'; signed integer overflow is undefined behavior. Some mainstream compilers removes handling of overflows when optimising the code and change the code to 'current>0'. [invalidTestForOverflow]
         */
        if (current + arr[i] > arr[i]) {
            current = current + arr[i];
        } else {
            current = arr[i];
        }
        if (current > best) {
            best = current;
        }
    }

    if (best > INT_MAX || best < INT_MIN) {
        return -1;
    }

    *result = (int)best;
    return 0;
}

int main(void)
{
    int arr[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int result = 0;

    if (max_subarray_sum(arr, n, &result) != 0) {
        fprintf(stderr, "Error: could not compute maximum subarray sum\n");
        return EXIT_FAILURE;
    }

    if (printf("Largest sum of contiguous subarray: %d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}