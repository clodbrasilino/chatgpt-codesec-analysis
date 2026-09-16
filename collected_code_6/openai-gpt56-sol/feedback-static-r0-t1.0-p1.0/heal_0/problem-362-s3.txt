#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static int find_most_frequent(const int *items, size_t count,
                              int *result, size_t *occurrences)
{
    int *copy = NULL;
    int best_item;
    int current_item;
    size_t best_count = 1;
    size_t current_count = 1;

    if (items == NULL || result == NULL || occurrences == NULL || count == 0) {
        return -1;
    }

    if (count > SIZE_MAX / sizeof(*copy)) {
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

    return 0;
}

int main(void)
{
    int items[] = {4, 2, 7, 4, 2, 4, 9, 4, 7, 2};
    const size_t count = sizeof(items) / sizeof(items[0]);
    int most_frequent;
    size_t occurrences;

    if (find_most_frequent(items, count, &most_frequent, &occurrences) != 0) {
        if (errno != 0) {
            perror("find_most_frequent");
        } else {
            fputs("Unable to find the most frequent item\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (printf("%d occurs %zu times\n", most_frequent, occurrences) < 0) {
        fputs("Failed to write output\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}