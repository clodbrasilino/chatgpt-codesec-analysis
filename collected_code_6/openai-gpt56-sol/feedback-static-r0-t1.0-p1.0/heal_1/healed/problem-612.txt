#include <stdint.h>
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
    size_t first_bytes;
    size_t last_bytes;
    size_t total_bytes;
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

    if (lists[first].length > SIZE_MAX / sizeof(int) ||
        lists[last].length > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    first_bytes = lists[first].length * sizeof(int);
    last_bytes = lists[last].length * sizeof(int);

    if (first_bytes > SIZE_MAX - last_bytes) {
        return -1;
    }

    total_bytes = first_bytes + last_bytes;
    merged = malloc(total_bytes);
    if (merged == NULL) {
        return -1;
    }

    memcpy(merged, lists[first].items, first_bytes);
    memcpy((unsigned char *)merged + first_bytes,
           lists[last].items, last_bytes);

    free(lists[first].items);
    free(lists[last].items);

    lists[first].items = merged;
    lists[first].length = total_bytes / sizeof(int);
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
        lists[i].items = NULL;
        lists[i].length = 0;
    }

    free(lists);
}

static void print_lists(const IntList *lists, size_t count)
{
    size_t i;
    size_t j;

    if (lists == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        putchar('[');

        if (lists[i].items != NULL) {
            for (j = 0; j < lists[i].length; ++j) {
                if (j != 0) {
                    fputs(", ", stdout);
                }
                printf("%d", lists[i].items[j]);
            }
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

    if (count > SIZE_MAX / sizeof(*lists)) {
        fputs("Allocation size overflow\n", stderr);
        return EXIT_FAILURE;
    }

    lists = calloc(count, sizeof(*lists));
    if (lists == NULL) {
        fputs("Allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        size_t length = sizeof(values[i]) / sizeof(values[i][0]);
        size_t bytes;

        if (length > SIZE_MAX / sizeof(*lists[i].items)) {
            fputs("Allocation size overflow\n", stderr);
            free_lists(lists, count);
            return EXIT_FAILURE;
        }

        bytes = length * sizeof(*lists[i].items);
        lists[i].items = malloc(bytes);
        if (lists[i].items == NULL) {
            fputs("Allocation failed\n", stderr);
            free_lists(lists, count);
            return EXIT_FAILURE;
        }

        memcpy(lists[i].items, values[i], bytes);
        lists[i].length = length;
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