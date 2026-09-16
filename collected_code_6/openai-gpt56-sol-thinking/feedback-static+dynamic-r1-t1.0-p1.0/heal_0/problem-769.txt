#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *items;
    size_t count;
} IntList;

static bool contains(const int *items, size_t count, int value)
{
    size_t i;

    for (i = 0; i < count; ++i) {
        if (items[i] == value) {
            return true;
        }
    }

    return false;
}

static bool list_difference(const int *first, size_t first_count,
                            const int *second, size_t second_count,
                            IntList *result)
{
    size_t i;
    size_t result_count;
    int *items;

    if (result == NULL ||
        (first == NULL && first_count != 0U) ||
        (second == NULL && second_count != 0U)) {
        return false;
    }

    result->items = NULL;
    result->count = 0U;
    result_count = 0U;

    for (i = 0; i < first_count; ++i) {
        if (!contains(second, second_count, first[i])) {
            ++result_count;
        }
    }

    if (result_count == 0U) {
        return true;
    }

    if (result_count > SIZE_MAX / sizeof(*items)) {
        return false;
    }

    items = malloc(result_count * sizeof(*items));
    if (items == NULL) {
        return false;
    }

    result_count = 0U;

    for (i = 0; i < first_count; ++i) {
        if (!contains(second, second_count, first[i])) {
            items[result_count] = first[i];
            ++result_count;
        }
    }

    result->items = items;
    result->count = result_count;

    return true;
}

static void free_int_list(IntList *list)
{
    if (list != NULL) {
        free(list->items);
        list->items = NULL;
        list->count = 0U;
    }
}

int main(void)
{
    const int first[] = {1, 2, 3, 4, 5, 3};
    const int second[] = {2, 4, 6};
    const size_t first_count = sizeof(first) / sizeof(first[0]);
    const size_t second_count = sizeof(second) / sizeof(second[0]);
    IntList difference;
    size_t i;

    if (!list_difference(first, first_count, second, second_count,
                         &difference)) {
        fputs("Unable to calculate list difference.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < difference.count; ++i) {
        printf("%d%s", difference.items[i],
               i + 1U < difference.count ? " " : "\n");
    }

    free_int_list(&difference);

    return EXIT_SUCCESS;
}