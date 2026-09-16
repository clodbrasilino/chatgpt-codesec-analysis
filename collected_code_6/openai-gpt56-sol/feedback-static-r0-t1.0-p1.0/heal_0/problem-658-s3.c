#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int find_most_frequent(const int *items, size_t count, int *result)
{
    int *copy;
    int most_frequent;
    size_t current_count = 1;
    size_t maximum_count = 1;

    if (items == NULL || result == NULL || count == 0 ||
        count > SIZE_MAX / sizeof(*copy)) {
        return -1;
    }

    copy = malloc(count * sizeof(*copy));
    if (copy == NULL) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        copy[i] = items[i];
    }

    qsort(copy, count, sizeof(*copy), compare_ints);
    most_frequent = copy[0];

    for (size_t i = 1; i < count; ++i) {
        if (copy[i] == copy[i - 1]) {
            ++current_count;
        } else {
            current_count = 1;
        }

        if (current_count > maximum_count) {
            maximum_count = current_count;
            most_frequent = copy[i];
        }
    }

    free(copy);
    *result = most_frequent;
    return 0;
}

int main(void)
{
    const int items[] = {4, 2, 7, 4, 3, 2, 4, 7, 4};
    const size_t count = sizeof(items) / sizeof(items[0]);
    int result;

    if (find_most_frequent(items, count, &result) != 0) {
        fputs("Unable to find the most frequent item.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}