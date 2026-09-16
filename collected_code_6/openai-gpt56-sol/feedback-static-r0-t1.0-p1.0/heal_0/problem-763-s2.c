#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static int minimum_difference(const int *array, size_t length, uintmax_t *result)
{
    int *copy = NULL;
    uintmax_t minimum = UINTMAX_MAX;
    size_t i;

    if (array == NULL || result == NULL || length < 2 ||
        length > SIZE_MAX / sizeof(*copy)) {
        return -1;
    }

    copy = malloc(length * sizeof(*copy));
    if (copy == NULL) {
        return -1;
    }

    for (i = 0; i < length; ++i) {
        copy[i] = array[i];
    }

    qsort(copy, length, sizeof(*copy), compare_ints);

    for (i = 1; i < length; ++i) {
        const intmax_t current = copy[i];
        const intmax_t previous = copy[i - 1];
        const uintmax_t difference = (uintmax_t)(current - previous);

        if (difference < minimum) {
            minimum = difference;
        }
    }

    free(copy);
    *result = minimum;
    return 0;
}

int main(void)
{
    int values[] = {8, 1, 15, 3, -4};
    const size_t length = sizeof(values) / sizeof(values[0]);
    uintmax_t result;

    errno = 0;
    if (minimum_difference(values, length, &result) != 0) {
        if (errno != 0) {
            perror("minimum_difference");
        } else {
            fputs("Unable to calculate the minimum difference.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (printf("Minimum difference: %ju\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}