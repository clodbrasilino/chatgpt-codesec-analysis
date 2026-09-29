#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static bool tuple_is_distinct(const int *tuple, size_t length)
{
    int *copy;
    size_t i;

    if (tuple == NULL && length != 0U) {
        return false;
    }

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
        copy[i] = tuple[i];
    }

    qsort(copy, length, sizeof(*copy), compare_ints);

    for (i = 1U; i < length; ++i) {
        if (copy[i - 1U] == copy[i]) {
            free(copy);
            return false;
        }
    }

    free(copy);
    return true;
}

int main(void)
{
    int tuple[] = {1, 2, 3, 4, 5};
    size_t length = sizeof(tuple) / sizeof(tuple[0]);

    if (tuple_is_distinct(tuple, length)) {
        puts("The tuple is distinct.");
    } else {
        puts("The tuple is not distinct.");
    }

    return EXIT_SUCCESS;
}