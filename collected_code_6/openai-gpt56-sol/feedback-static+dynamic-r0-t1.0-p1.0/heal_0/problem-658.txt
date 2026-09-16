#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int value;
    size_t count;
} Frequency;

static int compare_frequencies(const void *left, const void *right)
{
    const Frequency *a = left;
    const Frequency *b = right;

    if (a->value < b->value) {
        return -1;
    }
    if (a->value > b->value) {
        return 1;
    }
    return 0;
}

static int find_most_frequent(const int *items, size_t length,
                              int *result, size_t *occurrences)
{
    Frequency *frequencies;
    size_t i;
    size_t best_index;
    size_t unique_count;

    if (items == NULL || result == NULL || occurrences == NULL || length == 0) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*frequencies)) {
        return 0;
    }

    frequencies = malloc(length * sizeof(*frequencies));
    if (frequencies == NULL) {
        return 0;
    }

    for (i = 0; i < length; ++i) {
        frequencies[i].value = items[i];
        frequencies[i].count = 1;
    }

    qsort(frequencies, length, sizeof(*frequencies), compare_frequencies);

    unique_count = 1;
    for (i = 1; i < length; ++i) {
        if (frequencies[i].value == frequencies[unique_count - 1].value) {
            ++frequencies[unique_count - 1].count;
        } else {
            frequencies[unique_count] = frequencies[i];
            frequencies[unique_count].count = 1;
            ++unique_count;
        }
    }

    best_index = 0;
    for (i = 1; i < unique_count; ++i) {
        if (frequencies[i].count > frequencies[best_index].count) {
            best_index = i;
        }
    }

    *result = frequencies[best_index].value;
    *occurrences = frequencies[best_index].count;

    free(frequencies);
    return 1;
}

int main(void)
{
    int items[] = {4, 2, 4, 3, 2, 4, 5, 2, 4};
    const size_t length = sizeof(items) / sizeof(items[0]);
    int most_frequent;
    size_t occurrences;

    if (!find_most_frequent(items, length, &most_frequent, &occurrences)) {
        fputs("Unable to determine the most frequent item.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Item: %d\nOccurrences: %zu\n",
               most_frequent, occurrences) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}