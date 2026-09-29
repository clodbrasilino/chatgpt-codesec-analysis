#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int find_most_frequent(const int *items, size_t count, int *result, size_t *occurrences)
{
    int *copy = NULL;
    size_t best_count = 1;
    size_t current_count = 1;
    int best_item;

    if (items == NULL || result == NULL || occurrences == NULL || count == 0 ||
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
    best_item = copy[0];

    for (size_t i = 1; i < count; ++i) {
        if (copy[i] == copy[i - 1]) {
            ++current_count;
        } else {
            current_count = 1;
        }

        if (current_count > best_count) {
            best_count = current_count;
            best_item = copy[i];
        }
    }

    free(copy);
    *result = best_item;
    *occurrences = best_count;
    return 0;
}

int main(void)
{
    const int items[] = {4, 2, 7, 4, 2, 4, 9, 2, 4};
    const size_t count = sizeof(items) / sizeof(items[0]);
    int item;
    size_t occurrences;

    if (find_most_frequent(items, count, &item, &occurrences) != 0) {
        fputs("Unable to find the most frequent item.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Item: %d\nOccurrences: %zu\n", item, occurrences) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}