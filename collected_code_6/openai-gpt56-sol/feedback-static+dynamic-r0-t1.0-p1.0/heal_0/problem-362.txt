#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static bool find_most_frequent(const int *items, size_t count,
                               int *result, size_t *occurrences)
{
    int *copy = NULL;
    size_t best_count = 1;
    size_t current_count = 1;
    int best_item;
    int current_item;

    if (items == NULL || result == NULL || occurrences == NULL || count == 0) {
        return false;
    }

    if (count > SIZE_MAX / sizeof(*copy)) {
        return false;
    }

    copy = malloc(count * sizeof(*copy));
    if (copy == NULL) {
        return false;
    }

    for (size_t i = 0; i < count; ++i) {
        copy[i] = items[i];
    }

    qsort(copy, count, sizeof(*copy), compare_ints);

    best_item = copy[0];
    current_item = copy[0];

    for (size_t i = 1; i < count; ++i) {
        if (copy[i] == current_item) {
            ++current_count;
        } else {
            if (current_count > best_count) {
                best_count = current_count;
                best_item = current_item;
            }

            current_item = copy[i];
            current_count = 1;
        }
    }

    if (current_count > best_count) {
        best_count = current_count;
        best_item = current_item;
    }

    free(copy);
    *result = best_item;
    *occurrences = best_count;

    return true;
}

int main(void)
{
    const int items[] = {4, 2, 7, 4, 8, 4, 2, 7, 7, 7};
    const size_t count = sizeof(items) / sizeof(items[0]);
    int most_frequent;
    size_t occurrences;

    if (!find_most_frequent(items, count, &most_frequent, &occurrences)) {
        fputs("Unable to find the most frequent item.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Item: %d\nOccurrences: %zu\n",
               most_frequent, occurrences) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}