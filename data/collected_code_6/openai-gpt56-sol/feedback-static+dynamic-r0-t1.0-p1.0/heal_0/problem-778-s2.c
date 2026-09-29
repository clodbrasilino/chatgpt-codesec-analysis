#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    size_t count;
} Group;

static void free_groups(Group *groups, size_t group_count)
{
    if (groups == NULL) {
        return;
    }

    for (size_t i = 0; i < group_count; ++i) {
        free(groups[i].values);
    }

    free(groups);
}

static int pack_consecutive_duplicates(const int *input, size_t length,
                                       Group **result, size_t *result_count)
{
    Group *groups = NULL;
    size_t group_count = 0;
    size_t start = 0;

    if (result == NULL || result_count == NULL ||
        (input == NULL && length != 0)) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if (length == 0) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*groups)) {
        return -1;
    }

    groups = calloc(length, sizeof(*groups));
    if (groups == NULL) {
        return -1;
    }

    while (start < length) {
        size_t end = start + 1;

        while (end < length && input[end] == input[start]) {
            ++end;
        }

        groups[group_count].count = end - start;

        if (groups[group_count].count >
            SIZE_MAX / sizeof(*groups[group_count].values)) {
            free_groups(groups, group_count);
            return -1;
        }

        groups[group_count].values =
            malloc(groups[group_count].count *
                   sizeof(*groups[group_count].values));

        if (groups[group_count].values == NULL) {
            free_groups(groups, group_count);
            return -1;
        }

        for (size_t i = 0; i < groups[group_count].count; ++i) {
            groups[group_count].values[i] = input[start + i];
        }

        ++group_count;
        start = end;
    }

    *result = groups;
    *result_count = group_count;
    return 0;
}

int main(void)
{
    const int input[] = {1, 1, 2, 3, 3, 3, 4, 4, 5};
    const size_t length = sizeof(input) / sizeof(input[0]);
    Group *groups = NULL;
    size_t group_count = 0;

    if (pack_consecutive_duplicates(input, length, &groups, &group_count) != 0) {
        fputs("Failed to pack the list.\n", stderr);
        return EXIT_FAILURE;
    }

    putchar('[');

    for (size_t i = 0; i < group_count; ++i) {
        if (i != 0) {
            fputs(", ", stdout);
        }

        putchar('[');

        for (size_t j = 0; j < groups[i].count; ++j) {
            if (j != 0) {
                fputs(", ", stdout);
            }

            if (printf("%d", groups[i].values[j]) < 0) {
                free_groups(groups, group_count);
                return EXIT_FAILURE;
            }
        }

        putchar(']');
    }

    if (puts("]") == EOF) {
        free_groups(groups, group_count);
        return EXIT_FAILURE;
    }

    free_groups(groups, group_count);
    return EXIT_SUCCESS;
}