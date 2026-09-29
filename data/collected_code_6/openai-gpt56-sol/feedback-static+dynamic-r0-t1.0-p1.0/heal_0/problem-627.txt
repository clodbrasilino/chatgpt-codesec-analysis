#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

static int compare_size_t(const void *left, const void *right)
{
    const size_t a = *(const size_t *)left;
    const size_t b = *(const size_t *)right;

    return (a > b) - (a < b);
}

static int find_smallest_missing(const long long array[], size_t length,
                                 size_t *result)
{
    size_t *values = NULL;
    size_t count = 0U;
    size_t expected = 0U;

    if (result == NULL || (array == NULL && length != 0U)) {
        return -1;
    }

    if (length > SIZE_MAX / sizeof(*values)) {
        return -1;
    }

    if (length != 0U) {
        values = malloc(length * sizeof(*values));
        if (values == NULL) {
            return -1;
        }
    }

    for (size_t i = 0U; i < length; ++i) {
        if (array[i] >= 0 && (unsigned long long)array[i] <= SIZE_MAX) {
            values[count++] = (size_t)array[i];
        }
    }

    qsort(values, count, sizeof(*values), compare_size_t);

    for (size_t i = 0U; i < count; ++i) {
        if (values[i] < expected) {
            continue;
        }

        if (values[i] > expected) {
            break;
        }

        if (expected == SIZE_MAX) {
            free(values);
            return -1;
        }

        ++expected;
    }

    free(values);
    *result = expected;
    return 0;
}

int main(void)
{
    size_t length = 0U;
    size_t missing = 0U;

    if (scanf("%zu", &length) != 1) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(long long)) {
        return EXIT_FAILURE;
    }

    long long *array = NULL;

    if (length != 0U) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < length; ++i) {
        if (scanf("%lld", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (find_smallest_missing(array, length, &missing) != 0) {
        free(array);
        return EXIT_FAILURE;
    }

    printf("%zu\n", missing);
    free(array);

    return EXIT_SUCCESS;
}