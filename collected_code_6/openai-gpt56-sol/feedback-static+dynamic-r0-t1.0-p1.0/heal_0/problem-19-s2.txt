#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static bool contains_duplicate(const int *array, size_t length)
{
    int *copy;
    size_t bytes;
    bool duplicate = false;

    if (length < 2U) {
        return false;
    }

    if (array == NULL || length > SIZE_MAX / sizeof(*array)) {
        return false;
    }

    bytes = length * sizeof(*array);
    copy = malloc(bytes);
    if (copy == NULL) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        copy[i] = array[i];
    }

    qsort(copy, length, sizeof(*copy), compare_ints);

    for (size_t i = 1U; i < length; ++i) {
        if (copy[i] == copy[i - 1U]) {
            duplicate = true;
            break;
        }
    }

    free(copy);
    return duplicate;
}

int main(void)
{
    const int values[] = {4, 2, 7, 1, 2, 9};
    const size_t length = sizeof(values) / sizeof(values[0]);

    if (contains_duplicate(values, length)) {
        if (printf("Duplicate found\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No duplicate found\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}