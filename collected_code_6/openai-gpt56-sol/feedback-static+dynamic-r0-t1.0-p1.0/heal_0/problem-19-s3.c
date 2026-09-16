#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static bool contains_duplicate(const int *array, size_t length, bool *result)
{
    int *copy;
    size_t i;

    if (result == NULL || (array == NULL && length != 0U)) {
        return false;
    }

    *result = false;

    if (length < 2U) {
        return true;
    }

    if (length > SIZE_MAX / sizeof(*copy)) {
        return false;
    }

    copy = malloc(length * sizeof(*copy));
    if (copy == NULL) {
        return false;
    }

    for (i = 0U; i < length; ++i) {
        copy[i] = array[i];
    }

    qsort(copy, length, sizeof(*copy), compare_ints);

    for (i = 1U; i < length; ++i) {
        if (copy[i] == copy[i - 1U]) {
            *result = true;
            break;
        }
    }

    free(copy);
    return true;
}

int main(void)
{
    const int values[] = {4, 7, 2, 9, 7};
    bool has_duplicate;

    if (!contains_duplicate(values, sizeof(values) / sizeof(values[0]),
                            &has_duplicate)) {
        fputs("Unable to check the array.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(has_duplicate ? "Duplicate found." : "No duplicates found.");
    return EXIT_SUCCESS;
}