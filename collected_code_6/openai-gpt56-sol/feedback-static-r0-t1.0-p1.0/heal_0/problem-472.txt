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

static bool contains_consecutive_numbers(const int *list, size_t length)
{
    int *copy;
    size_t i;

    if (list == NULL || length == 0U) {
        return false;
    }

    if (length == 1U) {
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
        copy[i] = list[i];
    }

    qsort(copy, length, sizeof(*copy), compare_ints);

    for (i = 1U; i < length; ++i) {
        if ((long long)copy[i] - (long long)copy[i - 1U] != 1LL) {
            free(copy);
            return false;
        }
    }

    free(copy);
    return true;
}

int main(void)
{
    int values[] = {5, 2, 3, 4, 1};
    const size_t length = sizeof(values) / sizeof(values[0]);

    puts(contains_consecutive_numbers(values, length) ? "Consecutive" : "Not consecutive");
    return EXIT_SUCCESS;
}