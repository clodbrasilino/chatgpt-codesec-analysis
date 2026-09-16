#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static long long kadane_over_copies(const int *arr, size_t n, int copies)
{
    long long best;
    long long current;
    size_t total;
    size_t i;

    total = n * (size_t)copies;
    best = arr[0];
    current = arr[0];

    for (i = 1; i < total; i++) {
        long long value = (long long)arr[i % n];
        if (current > 0) {
            current = current + value;
        } else {
            current = value;
        }
        if (current > best) {
            best = current;
        }
    }
    return best;
}

int max_repeated_subarray_sum(const int *arr, size_t n, int k, long long *result)
{
    long long total_sum;
    long long best;
    size_t i;

    if (arr == NULL || result == NULL || n == 0 || k <= 0) {
        return -1;
    }

    if (k == 1) {
        *result = kadane_over_copies(arr, n, 1);
        return 0;
    }

    total_sum = 0;
    for (i = 0; i < n; i++) {
        total_sum += (long long)arr[i];
    }

    best = kadane_over_copies(arr, n, 2);

    if (total_sum > 0 && k > 2) {
        long long extended = best + (long long)(k - 2) * total_sum;
        if (extended > best) {
            best = extended;
        }
    }

    *result = best;
    return 0;
}

int main(void)
{
    int arr[] = { 10, 20, -30, -1 };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;
    long long result;

    if (max_repeated_subarray_sum(arr, n, k, &result) != 0) {
        if (fprintf(stderr, "Invalid input\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Largest sum of contiguous subarray: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}