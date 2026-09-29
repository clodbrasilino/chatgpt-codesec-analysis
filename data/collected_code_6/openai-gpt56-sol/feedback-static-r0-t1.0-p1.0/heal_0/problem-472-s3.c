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

static bool contains_consecutive_numbers(const int *list, size_t count)
{
    int *copy = NULL;
    bool consecutive = true;
    size_t i;

    if (list == NULL || count == 0U) {
        return false;
    }

    if (count == 1U) {
        return true;
    }

    if (count > SIZE_MAX / sizeof(*copy)) {
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
        if ((long long)copy[i] - (long long)copy[i - 1U] != 1LL) {
            consecutive = false;
            break;
        }
    }

    free(copy);
    return consecutive;
}

int main(void)
{
    int list[] = {5, 2, 4, 3, 1};
    const size_t count = sizeof(list) / sizeof(list[0]);

    if (contains_consecutive_numbers(list, count)) {
        puts("The list contains consecutive numbers.");
    } else {
        puts("The list does not contain consecutive numbers.");
    }

    return EXIT_SUCCESS;
}