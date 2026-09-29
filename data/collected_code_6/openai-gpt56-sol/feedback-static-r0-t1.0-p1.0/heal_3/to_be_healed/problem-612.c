#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static int merge_first_and_last(IntList *lists, size_t count)
{
    size_t first = 0;
    size_t last;
    size_t total_length;
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

    if (lists[first].length > SIZE_MAX - lists[last].length) {
        return -1;
    }

    total_length = lists[first].length + lists[last].length;

    if (checked_array_size(lists[first].length, sizeof(*merged),
                           &first_bytes) != 0 ||
        checked_array_size(lists[last].length, sizeof(*merged),
                           &last_bytes) != 0 ||
        checked_array_size(total_length, sizeof(*merged),
                           &total_bytes) != 0) {
        return -1;
    }

    merged = malloc(total_bytes);
    if (merged == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(merged, lists[first].items, first_bytes);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(merged + lists[first].length, lists[last].items, last_bytes);

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

static void print_lists(const IntList *lists, size_t count)
{
    size_t i;
    size_t j;

    if (lists == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        putchar('[');

        for (j = 0; j < lists[i].length; ++j) {
            if (j != 0) {
                fputs(", ", stdout);
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

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
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