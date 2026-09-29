#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

static bool is_unique(const int *arr, size_t len, size_t index)
{
    size_t i;

    for (i = 0; i < len; i++) {
        if (i != index && arr[i] == arr[index]) {
            return false;
        }
    }
    return true;
}

static bool product_of_unique(const int *arr, size_t len, long long *result)
{
    size_t i;
    long long product = 1;
    bool found = false;

    if (arr == NULL || result == NULL) {
        return false;
    }

    for (i = 0; i < len; i++) {
        if (is_unique(arr, len, i)) {
            long long value = (long long)arr[i];
            long long magnitude = llabs(value);

            if (value != 0 && magnitude != 0 &&
                (product > LLONG_MAX / magnitude ||
                 product < LLONG_MIN / magnitude)) {
                return false;
            }
            product *= value;
            found = true;
        }
    }

    if (!found) {
        return false;
    }

    *result = product;
    return true;
}

int main(void)
{
    int numbers[] = {10, 20, 30, 40, 20, 50, 60, 40};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    long long result = 0;

    if (product_of_unique(numbers, count, &result)) {
        if (printf("Product of unique numbers: %lld\n", result) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (fprintf(stderr, "No unique numbers found or overflow occurred\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}