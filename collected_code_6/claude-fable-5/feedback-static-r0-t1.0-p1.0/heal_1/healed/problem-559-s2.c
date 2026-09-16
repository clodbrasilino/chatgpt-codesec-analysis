#include <stdio.h>
#include <limits.h>
#include <stddef.h>

long long max_subarray_sum(const int *arr, size_t n, int *status)
{
    if (arr == NULL || n == 0U || status == NULL) {
        if (status != NULL) {
            *status = -1;
        }
        return 0;
    }

    long long best = (long long)arr[0];
    long long current = (long long)arr[0];

    for (size_t i = 1U; i < n; i++) {
        long long value = (long long)arr[i];

        if (current > 0) {
            if (value > 0 && current > LLONG_MAX - value) {
                *status = -2;
                return 0;
            }
            current = current + value;
        } else {
            current = value;
        }

        if (current > best) {
            best = current;
        }
    }

    *status = 0;
    return best;
}

int main(void)
{
    int data[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
    size_t n = sizeof(data) / sizeof(data[0]);
    int status = 0;

    long long result = max_subarray_sum(data, n, &status);

    if (status != 0) {
        if (fprintf(stderr, "Error: invalid input\n") < 0) {
            return 1;
        }
        return 1;
    }

    if (printf("Largest contiguous subarray sum: %lld\n", result) < 0) {
        return 1;
    }

    return 0;
}