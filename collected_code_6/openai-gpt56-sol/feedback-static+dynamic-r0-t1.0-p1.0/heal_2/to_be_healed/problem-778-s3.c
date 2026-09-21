#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t count;
} Group;

static void free_groups(Group *groups, size_t group_count)
{
    if (groups == NULL) {
        return;
    }

    for (size_t i = 0; i < group_count; ++i) {
        free(groups[i].elements);
    }

    free(groups);
}

static int pack_consecutive_duplicates(const int *values, size_t value_count,
                                       Group **result, size_t *result_count)
{
    Group *groups;
    size_t group_count = 0;
    size_t start = 0;

    if (result == NULL || result_count == NULL ||
        (value_count != 0 && values == NULL)) {
        return 0;
    }

    *result = NULL;
    *result_count = 0;

    if (value_count == 0) {
        return 1;
    }

    if (value_count > SIZE_MAX / sizeof(*groups)) {
        return 0;
    }

    groups = calloc(value_count, sizeof(*groups));
    if (groups == NULL) {
        return 0;
    }

    while (start < value_count) {
        size_t end = start + 1;
        size_t count;
        size_t byte_count;

        while (end < value_count && values[end] == values[start]) {
            ++end;
        }

        count = end - start;

        if (count > SIZE_MAX / sizeof(*values)) {
            free_groups(groups, group_count);
            return 0;
        }

        byte_count = count * sizeof(*values);
        groups[group_count].elements = malloc(byte_count);
        if (groups[group_count].elements == NULL) {
            free_groups(groups, group_count);
            return 0;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(groups[group_count].elements, &values[start], byte_count);
        groups[group_count].count = count;

        ++group_count;
        start = end;
    }

    *result = groups;
    *result_count = group_count;
    return 1;
}

static void print_groups(const Group *groups, size_t group_count)
{
    putchar('[');

    for (size_t i = 0; i < group_count; ++i) {
        putchar('[');

        for (size_t j = 0; j < groups[i].count; ++j) {
            printf("%d", groups[i].elements[j]);

            if (j + 1 < groups[i].count) {
                printf(", ");
            }
        }

        putchar(']');

        if (i + 1 < group_count) {
            printf(", ");
        }
    }

    printf("]\n");
}

int main(void)
{
    const int values[] = {1, 1, 2, 3, 3, 3, 4, 4, 5};
    const size_t value_count = sizeof(values) / sizeof(values[0]);
    Group *groups = NULL;
    size_t group_count = 0;

    if (!pack_consecutive_duplicates(values, value_count,
                                     &groups, &group_count)) {
        fprintf(stderr, "Failed to pack the list.\n");
        return EXIT_FAILURE;
    }

    print_groups(groups, group_count);
    free_groups(groups, group_count);

    return EXIT_SUCCESS;
}