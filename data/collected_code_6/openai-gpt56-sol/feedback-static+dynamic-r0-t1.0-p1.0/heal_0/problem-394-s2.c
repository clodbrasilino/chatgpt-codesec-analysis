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

static bool is_distinct(const int *tuple, size_t length)
{
    int *copy;
    bool distinct = true;

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

    for (size_t i = 0U; i < length; ++i) {
        copy[i] = tuple[i];
    }

    qsort(copy, length, sizeof(*copy), compare_ints);

    for (size_t i = 1U; i < length; ++i) {
        if (copy[i] == copy[i - 1U]) {
            distinct = false;
            break;
        }
    }

    free(copy);
    return distinct;
}

int main(void)
{
    int tuple[] = {1, 2, 3, 4, 5};
    const size_t length = sizeof(tuple) / sizeof(tuple[0]);

    if (is_distinct(tuple, length)) {
        puts("The tuple is distinct.");
    } else {
        puts("The tuple is not distinct.");
    }

    return EXIT_SUCCESS;
}