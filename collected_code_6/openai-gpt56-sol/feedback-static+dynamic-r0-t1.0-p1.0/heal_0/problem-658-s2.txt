#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int value;
    size_t index;
} Item;

static int compare_items(const void *left, const void *right)
{
    const Item *a = left;
    const Item *b = right;

    if (a->value < b->value) {
        return -1;
    }
    if (a->value > b->value) {
        return 1;
    }
    if (a->index < b->index) {
        return -1;
    }
    if (a->index > b->index) {
        return 1;
    }
    return 0;
}

static bool find_most_frequent(const int *values, size_t count,
                               int *result, size_t *occurrences)
{
    Item *items = NULL;
    size_t best_count = 0;
    size_t best_index = 0;
    int best_value = 0;

    if (values == NULL || result == NULL || occurrences == NULL ||
        count == 0 || count > SIZE_MAX / sizeof(*items)) {
        return false;
    }

    items = malloc(count * sizeof(*items));
    if (items == NULL) {
        return false;
    }

    for (size_t i = 0; i < count; ++i) {
        items[i].value = values[i];
        items[i].index = i;
    }

    qsort(items, count, sizeof(*items), compare_items);

    for (size_t start = 0; start < count;) {
        size_t end = start + 1;

        while (end < count && items[end].value == items[start].value) {
            ++end;
        }

        const size_t current_count = end - start;
        const size_t current_index = items[start].index;

        if (current_count > best_count ||
            (current_count == best_count && current_index < best_index)) {
            best_count = current_count;
            best_index = current_index;
            best_value = items[start].value;
        }

        start = end;
    }

    free(items);
    *result = best_value;
    *occurrences = best_count;
    return true;
}

int main(void)
{
    int values[] = {4, 2, 7, 2, 4, 2, 7, 7, 7};
    const size_t count = sizeof(values) / sizeof(values[0]);
    int result = 0;
    size_t occurrences = 0;

    if (!find_most_frequent(values, count, &result, &occurrences)) {
        fputs("Unable to determine the most frequent item.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Item: %d\nOccurrences: %zu\n", result, occurrences) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}