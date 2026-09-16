#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static int find_minimum(const int *array, size_t length, int *minimum)
{
    if (array == NULL || minimum == NULL || length == 0U) {
        return -1;
    }

    size_t left = 0U;
    size_t right = length - 1U;

    while (left < right) {
        const size_t middle = left + (right - left) / 2U;

        if (array[middle] < array[right]) {
            right = middle;
        } else if (array[middle] > array[right]) {
            left = middle + 1U;
        } else {
            --right;
        }
    }

    *minimum = array[left];
    return 0;
}

int main(void)
{
    size_t length = 0U;

    if (scanf("%zu", &length) != 1 || length == 0U ||
        length > SIZE_MAX / sizeof(int)) {
        fputs("Invalid array length\n", stderr);
        return EXIT_FAILURE;
    }

    int *array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        long value = 0L;

        errno = 0;
        if (scanf("%ld", &value) != 1 || errno == ERANGE ||
            value < INT_MIN || value > INT_MAX) {
            fputs("Invalid array element\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }

        array[i] = (int)value;
    }

    int minimum = 0;
    if (find_minimum(array, length, &minimum) != 0) {
        fputs("Unable to find minimum\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    printf("%d\n", minimum);

    free(array);
    return EXIT_SUCCESS;
}