#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool product_first_even_odd(const int *arr, size_t len, long long *result)
{
    bool found_even = false;
    bool found_odd = false;
    int first_even = 0;
    int first_odd = 0;
    size_t i;

    if (arr == NULL || result == NULL || len == 0U) {
        return false;
    }

    for (i = 0U; i < len; i++) {
        if ((arr[i] % 2) == 0) {
            if (!found_even) {
                first_even = arr[i];
                found_even = true;
            }
        } else {
            if (!found_odd) {
                first_odd = arr[i];
                found_odd = true;
            }
        }
        if (found_even && found_odd) {
            break;
        }
    }

    if (!found_even || !found_odd) {
        return false;
    }

    *result = (long long)first_even * (long long)first_odd;
    return true;
}

int main(void)
{
    int numbers[] = {1, 3, 5, 7, 4, 1, 6, 8};
    size_t len = sizeof(numbers) / sizeof(numbers[0]);
    long long product = 0;

    if (product_first_even_odd(numbers, len, &product)) {
        if (printf("Product of first even and first odd: %lld\n", product) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (fprintf(stderr, "List does not contain both an even and an odd number.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}