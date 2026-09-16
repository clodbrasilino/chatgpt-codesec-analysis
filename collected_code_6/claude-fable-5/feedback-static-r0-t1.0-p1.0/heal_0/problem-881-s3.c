#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int sum_first_even_odd(const int *arr, size_t len, int *result)
{
    int first_even = 0;
    int first_odd = 0;
    int found_even = 0;
    int found_odd = 0;
    size_t i;

    if (arr == NULL || result == NULL || len == 0) {
        return -1;
    }

    for (i = 0; i < len; i++) {
        if (!found_even && (arr[i] % 2) == 0) {
            first_even = arr[i];
            found_even = 1;
        }
        if (!found_odd && (arr[i] % 2) != 0) {
            first_odd = arr[i];
            found_odd = 1;
        }
        if (found_even && found_odd) {
            break;
        }
    }

    if (!found_even || !found_odd) {
        return -1;
    }

    if ((first_odd > 0 && first_even > INT_MAX - first_odd) ||
        (first_odd < 0 && first_even < INT_MIN - first_odd)) {
        return -1;
    }

    *result = first_even + first_odd;
    return 0;
}

int main(void)
{
    int numbers[] = {3, 8, 5, 12, 7, 4};
    size_t len = sizeof(numbers) / sizeof(numbers[0]);
    int sum = 0;

    if (sum_first_even_odd(numbers, len, &sum) != 0) {
        fprintf(stderr, "Error: could not compute sum of first even and odd numbers\n");
        return EXIT_FAILURE;
    }

    if (printf("Sum of first even and first odd: %d\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}