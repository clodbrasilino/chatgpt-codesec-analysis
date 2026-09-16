#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int compare_size_t(const void *lhs, const void *rhs)
{
    const size_t a = *(const size_t *)lhs;
    const size_t b = *(const size_t *)rhs;

    return (a > b) - (a < b);
}

static int find_smallest_missing(const size_t *array, size_t length, size_t *result)
{
    size_t *copy;
    size_t expected = 0U;

    if (result == NULL || (array == NULL && length != 0U)) {
        return -1;
    }

    if (length == 0U) {
        *result = 0U;
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*copy)) {
        return -1;
    }

    copy = malloc(length * sizeof(*copy));
    if (copy == NULL) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        copy[i] = array[i];
    }

    qsort(copy, length, sizeof(*copy), compare_size_t);

    for (size_t i = 0U; i < length; ++i) {
        if (copy[i] == expected) {
            if (expected == SIZE_MAX) {
                free(copy);
                return -1;
            }
            ++expected;
        } else if (copy[i] > expected) {
            break;
        }
    }

    free(copy);
    *result = expected;
    return 0;
}

int main(void)
{
    size_t array[] = {3U, 0U, 1U, 4U, 1U};
    const size_t length = sizeof(array) / sizeof(array[0]);
    size_t missing;

    if (find_smallest_missing(array, length, &missing) != 0) {
        fputs("Unable to find the smallest missing number.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", missing) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}