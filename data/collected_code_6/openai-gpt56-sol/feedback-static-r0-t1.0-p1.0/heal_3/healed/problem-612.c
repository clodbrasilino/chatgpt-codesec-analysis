#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *items;
    size_t length;
} IntList;

static int checked_array_size(size_t count, size_t element_size, size_t *bytes)
{
    if (bytes == NULL || (element_size != 0 && count > SIZE_MAX / element_size)) {
        return -1;
    }

    *bytes = count * element_size;
    return 0;
}

static int copy_ints(int *destination, size_t destination_count,
                     const int *source, size_t source_count)
{
    size_t i;

    if (source_count > destination_count) {
        return -1;
    }

    if (source_count != 0 && (destination == NULL || source == NULL)) {
        return -1;
    }

    for (i = 0; i < source_count; ++i) {
        destination[i] = source[i];
    }

    return 0;
}

static int merge_first_and_last(IntList *lists, size_t count)
{
    size_t first = 0;
    size_t last;
    size_t total_length;
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

    if (lists[first].length > SIZE_MAX - lists[last].length) {
        return -1;
    }

    total_length = lists[first].length + lists[last].length;

    if (checked_array_size(total_length, sizeof(*merged), &total_bytes) != 0) {
        return -1;
    }

    merged = malloc(total_bytes);
    if (merged == NULL) {
        return -1;
    }

    if (copy_ints(merged, total_length, lists[first].items,
                  lists[first].length) != 0 ||
        copy_ints(merged + lists[first].length,
                  total_length - lists[first].length,
                  lists[last].items, lists[last].length) != 0) {
        free(merged);
        return -1;
    }

    free(lists[first].items);
    free(lists[last].items);

    lists[first].items = merged;
    lists[first].length = total_length;
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

        if (putchar('[') == EOF) {
            return -1;
        }

        for (j = 0; j < lists[i].length; ++j) {
            if (j != 0 && fputs(", ", stdout) == EOF) {
                return -1;
            }

            if (printf("%d", lists[i].items[j]) < 0) {
                return -1;
            }
        }

        if (puts("]") == EOF) {
            return -1;
        }
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
    size_t list_bytes;
    size_t i;

    if (checked_array_size(count, sizeof(*lists), &list_bytes) != 0) {
        fputs("Allocation size overflow\n", stderr);
        return EXIT_FAILURE;
    }

    lists = calloc(1, list_bytes);
    if (lists == NULL) {
        fputs("Allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        const size_t length = sizeof(values[i]) / sizeof(values[i][0]);
        size_t bytes;

        if (checked_array_size(length, sizeof(*lists[i].items), &bytes) != 0) {
            fputs("Allocation size overflow\n", stderr);
            free_lists(lists, count);
            return EXIT_FAILURE;
        }

        lists[i].items = malloc(bytes);
        if (lists[i].items == NULL) {
            fputs("Allocation failed\n", stderr);
            free_lists(lists, count);
            return EXIT_FAILURE;
        }

        if (copy_ints(lists[i].items, length, values[i], length) != 0) {
            fputs("Copy failed\n", stderr);
            free_lists(lists, count);
            return EXIT_FAILURE;
        }

        lists[i].length = length;
    }

    if (merge_first_and_last(lists, count) != 0) {
        fputs("Merge failed\n", stderr);
        free_lists(lists, count);
        return EXIT_FAILURE;
    }

    if (print_lists(lists, count) != 0) {
        fputs("Output failed\n", stderr);
        free_lists(lists, count);
        return EXIT_FAILURE;
    }

    free_lists(lists, count);
    return EXIT_SUCCESS;
}