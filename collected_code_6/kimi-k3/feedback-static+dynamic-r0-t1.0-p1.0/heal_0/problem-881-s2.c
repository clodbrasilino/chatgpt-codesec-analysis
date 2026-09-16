#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int find_first_even_odd_sum(const int *arr, size_t size, long *result)
{
    int first_even = 0;
    int first_odd = 0;
    int found_even = 0;
    int found_odd = 0;
    size_t i;

    if (arr == NULL || result == NULL || size == 0) {
        return -1;
    }

    for (i = 0; i < size; i++) {
        if (!found_even && arr[i] % 2 == 0) {
            first_even = arr[i];
            found_even = 1;
        }
        if (!found_odd && arr[i] % 2 != 0) {
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

    if ((first_odd > 0 && first_even > LONG_MAX - first_odd) ||
        (first_odd < 0 && first_even < LONG_MIN - first_odd)) {
        return -1;
    }

    *result = (long)first_even + (long)first_odd;
    return 0;
}

int main(void)
{
    int arr[] = {1, 3, 5, 7, 8, 10, 12};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    long sum = 0;

    if (find_first_even_odd_sum(arr, size, &sum) == 0) {
        printf("Sum of first even and first odd: %ld\n", sum);
    } else {
        fprintf(stderr, "Error: Could not find both even and odd numbers or invalid input\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}