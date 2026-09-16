#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_even_odd_product(const int *arr, size_t size, long long *result)
{
    int first_even = 0;
    int first_odd = 0;
    int even_found = 0;
    int odd_found = 0;
    size_t i;

    if (arr == NULL || result == NULL || size == 0U) {
        return -1;
    }

    for (i = 0U; i < size; i++) {
        if ((arr[i] % 2) == 0) {
            if (even_found == 0) {
                first_even = arr[i];
                even_found = 1;
            }
        } else {
            if (odd_found == 0) {
                first_odd = arr[i];
                odd_found = 1;
            }
        }
        if ((even_found == 1) && (odd_found == 1)) {
            break;
        }
    }

    if ((even_found == 0) || (odd_found == 0)) {
        return -1;
    }

    *result = (long long)first_even * (long long)first_odd;
    return 0;
}

int main(void)
{
    int numbers[] = {1, 3, 5, 7, 4, 1, 6, 8};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    long long product = 0;

    if (find_even_odd_product(numbers, size, &product) != 0) {
        (void)fprintf(stderr, "Error: could not find both an even and an odd number\n");
        return EXIT_FAILURE;
    }

    if (printf("Product of first even and first odd number: %lld\n", product) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}