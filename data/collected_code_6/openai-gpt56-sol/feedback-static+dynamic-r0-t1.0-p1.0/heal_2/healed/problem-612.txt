#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *items;
    size_t length;
} IntList;

static int checked_int_array_size(size_t length, size_t *bytes)
{
    if (bytes == NULL || length > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    *bytes = length * sizeof(int);
    return 0;
}

static int merge_first_and_last(IntList *lists, size_t count)
{
    size_t first = 0;
    size_t last;
    size_t first_bytes;
    size_t last_bytes;
    size_t merged_bytes;
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

    if (checked_int_array_size(lists[first].length, &first_bytes) != 0 ||
        checked_int_array_size(lists[last].length, &last_bytes) != 0 ||
        first_bytes > SIZE_MAX - last_bytes) {
        return -1;
    }

    merged_bytes = first_bytes + last_bytes;

    if (merged_bytes / sizeof(int) !=
        lists[first].length + lists[last].length) {
        return -1;
    }

    merged = malloc(merged_bytes);
    if (merged == NULL) {
        return -1;
    }

    if (first_bytes > merged_bytes ||
        last_bytes > merged_bytes - first_bytes) {
        free(merged);
        return -1;
    }

    memcpy(merged, lists[first].items, first_bytes);
    memcpy((unsigned char *)merged + first_bytes,
           lists[last].items, last_bytes);

    free(lists[first].items);
    free(lists[last].items);

    lists[first].items = merged;
    lists[first].length = merged_bytes / sizeof(int);
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

static int print_lists(const IntList *lists, size_t count)
{
    size_t i;
    size_t j;

    if (lists == NULL && count != 0) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        if (lists[i].length != 0 && lists[i].items == NULL) {
            return -1;
        }

        putchar('[');

        for (j = 0; j < lists[i].length; ++j) {
            if (j != 0) {
                fputs(", ", stdout);
            }

            printf("%d", lists[i].items[j]);
        }

        puts("]");
    }

    return 0;
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
    size_t allocation_bytes;
    size_t i;

    if (count > SIZE_MAX / sizeof(*lists)) {
        fputs("Allocation size overflow\n", stderr);
        return EXIT_FAILURE;
    }

    allocation_bytes = count * sizeof(*lists);
    lists = calloc(1, allocation_bytes);
    if (lists == NULL) {
        fputs("Allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        size_t source_length = sizeof(values[i]) / sizeof(values[i][0]);
        size_t source_bytes = sizeof(values[i]);
        size_t destination_bytes;

        if (checked_int_array_size(source_length, &destination_bytes) != 0 ||
            source_bytes > destination_bytes ||
            source_bytes != destination_bytes) {
            fputs("Invalid copy size\n", stderr);
            free_lists(lists, count);
            return EXIT_FAILURE;
        }

        lists[i].items = malloc(destination_bytes);
        if (lists[i].items == NULL) {
            fputs("Allocation failed\n", stderr);
            free_lists(lists, count);
            return EXIT_FAILURE;
        }

        memcpy(lists[i].items, values[i], source_bytes);
        lists[i].length = source_length;
    }

    if (merge_first_and_last(lists, count) != 0) {
        fputs("Merge failed\n", stderr);
        free_lists(lists, count);
        return EXIT_FAILURE;
    }

    if (print_lists(lists, count) != 0) {
        fputs("Invalid list data\n", stderr);
        free_lists(lists, count);
        return EXIT_FAILURE;
    }

    free_lists(lists, count);
    return EXIT_SUCCESS;
}