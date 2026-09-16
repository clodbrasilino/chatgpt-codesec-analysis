#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int left = *(const int *)lhs;
    const int right = *(const int *)rhs;

    return (left > right) - (left < right);
}

static bool elements_are_unique(const int *list, size_t count)
{
    int *copy;
    size_t i;

    if (count < 2U) {
        return true;
    }

    if (list == NULL || count > SIZE_MAX / sizeof(*copy)) {
        return false;
    }

    copy = malloc(count * sizeof(*copy));
    if (copy == NULL) {
        return false;
    }

    for (i = 0U; i < count; ++i) {
        copy[i] = list[i];
    }

    qsort(copy, count, sizeof(*copy), compare_ints);

    for (i = 1U; i < count; ++i) {
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
    const int list[] = {4, 2, 7, 1, 9};
    const size_t count = sizeof(list) / sizeof(list[0]);

    if (elements_are_unique(list, count)) {
        puts("All elements are unique.");
    } else {
        puts("The elements are not unique.");
    }

    return EXIT_SUCCESS;
}