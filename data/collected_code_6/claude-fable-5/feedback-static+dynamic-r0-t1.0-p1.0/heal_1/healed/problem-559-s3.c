#include <stdio.h>
#include <stdlib.h>

long long max_subarray_sum(const int *arr, size_t n)
{
    long long best;
    long long current;
    size_t i;

    if (arr == NULL || n == 0) {
        return 0;
    }

    best = arr[0];
    current = arr[0];

    for (i = 1; i < n; i++) {
        if (current > 0) {
            current = current + (long long)arr[i];
        } else {
            current = arr[i];
        }
        if (current > best) {
            best = current;
        }
    }

    return best;
}

int main(void)
{
    int data[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
    size_t n = sizeof(data) / sizeof(data[0]);
    long long result;

    result = max_subarray_sum(data, n);

    if (printf("Largest sum of contiguous subarray: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}