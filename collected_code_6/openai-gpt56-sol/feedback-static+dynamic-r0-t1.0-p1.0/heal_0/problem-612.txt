#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *items;
    size_t length;
} IntList;

static int merge_first_and_last(IntList *lists, size_t count)
{
    size_t first = 0;
    size_t last;
    size_t new_length;
    int *merged;

    if (lists == NULL || count == 0) {
        return 0;
    }

    while (first < count && lists[first].length == 0) {
        ++first;
    }

    if (first == count) {
        return 0;
    }

    last = count - 1;
    while (last > first && lists[last].length == 0) {
        --last;
    }

    if (first == last) {
        return 0;
    }

    if (lists[first].items == NULL || lists[last].items == NULL) {
        return -1;
    }

    if (lists[first].length > SIZE_MAX - lists[last].length) {
        return -1;
    }

    new_length = lists[first].length + lists[last].length;

    if (new_length > SIZE_MAX / sizeof(*merged)) {
        return -1;
    }

    merged = malloc(new_length * sizeof(*merged));
    if (merged == NULL) {
        return -1;
    }

    memcpy(merged, lists[first].items,
           lists[first].length * sizeof(*merged));
    memcpy(merged + lists[first].length, lists[last].items,
           lists[last].length * sizeof(*merged));

    free(lists[first].items);
    free(lists[last].items);

    lists[first].items = merged;
    lists[first].length = new_length;
    lists[last].items = NULL;
    lists[last].length = 0;

    return 0;
}

static void free_lists(IntList *lists, size_t count)
{
    size_t i;

    if (lists == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free(lists[i].items);
    }

    free(lists);
}

static void print_lists(const IntList *lists, size_t count)
{
    size_t i;
    size_t j;

    for (i = 0; i < count; ++i) {
        putchar('[');
        for (j = 0; j < lists[i].length; ++j) {
            if (j != 0) {
                printf(", ");
            }
            printf("%d", lists[i].items[j]);
        }
        puts("]");
    }
}

int main(void)
{
    static const int values[][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    const size_t count = sizeof(values) / sizeof(values[0]);
    IntList *lists;
    size_t i;

    lists = calloc(count, sizeof(*lists));
    if (lists == NULL) {
        fputs("Allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        lists[i].length = sizeof(values[i]) / sizeof(values[i][0]);
        lists[i].items = malloc(lists[i].length * sizeof(*lists[i].items));

        if (lists[i].items == NULL) {
            fputs("Allocation failed\n", stderr);
            free_lists(lists, count);
            return EXIT_FAILURE;
        }

        memcpy(lists[i].items, values[i], sizeof(values[i]));
    }

    if (merge_first_and_last(lists, count) != 0) {
        fputs("Merge failed\n", stderr);
        free_lists(lists, count);
        return EXIT_FAILURE;
    }

    print_lists(lists, count);
    free_lists(lists, count);

    return EXIT_SUCCESS;
}