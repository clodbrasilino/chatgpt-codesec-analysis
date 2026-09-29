#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

static bool is_first_occurrence(const int *arr, size_t index)
{
    size_t i;

    for (i = 0; i < index; i++) {
        if (arr[i] == arr[index]) {
            return false;
        }
    }
    return true;
}

static bool product_of_unique(const int *arr, size_t len, long long *result)
{
    size_t i;
    long long product = 1LL;
    long long magnitude;

    if (arr == NULL || result == NULL || len == 0U) {
        return false;
    }

    for (i = 0; i < len; i++) {
        if (is_first_occurrence(arr, i)) {
            magnitude = (arr[i] < 0) ? -(long long)arr[i] : (long long)arr[i];
            if (magnitude != 0LL) {
                if ((product > 0LL ? product : -product) > LLONG_MAX / magnitude) {
                    return false;
                }
            }
            product *= (long long)arr[i];
        }
    }

    *result = product;
    return true;
}

int main(void)
{
    int numbers[] = { 2, 3, 2, 5, 3, 7 };
    size_t len = sizeof(numbers) / sizeof(numbers[0]);
    long long result = 0LL;

    if (product_of_unique(numbers, len, &result)) {
        if (printf("Product of unique numbers: %lld\n", result) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (fprintf(stderr, "Failed to compute product\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}