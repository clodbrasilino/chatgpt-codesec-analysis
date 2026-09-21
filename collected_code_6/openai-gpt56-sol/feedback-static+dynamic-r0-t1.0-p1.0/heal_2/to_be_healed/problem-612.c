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
    size_t new_length;
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

    if (lists[first].length > SIZE_MAX - lists[last].length) {
        return -1;
    }

    new_length = lists[first].length + lists[last].length;

    if (checked_int_array_size(lists[first].length, &first_bytes) != 0 ||
        checked_int_array_size(lists[last].length, &last_bytes) != 0 ||
        checked_int_array_size(new_length, &merged_bytes) != 0) {
        return -1;
    }

    merged = malloc(merged_bytes);
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
    memcpy((unsigned char *)merged + first_bytes,
           lists[last].items, last_bytes);

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
        size_t bytes = sizeof(values[i]);

        lists[i].length = sizeof(values[i]) / sizeof(values[i][0]);

        if (lists[i].length > SIZE_MAX / sizeof(*lists[i].items)) {
            fputs("Allocation size overflow\n", stderr);
            free_lists(lists, count);
            return EXIT_FAILURE;
        }

        if (bytes != lists[i].length * sizeof(*lists[i].items)) {
            fputs("Invalid copy size\n", stderr);
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