#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    const char *value;
} Pair;

typedef struct {
    int key;
    const char **values;
    size_t count;
} Group;

static void free_groups(Group *groups, size_t group_count)
{
    size_t i;
    if (groups == NULL) {
        return;
    }
    for (i = 0; i < group_count; i++) {
        free(groups[i].values);
    }
    free(groups);
}

static Group *sort_on_occurrence(const Pair *pairs, size_t n, size_t *group_count)
{
    Group *groups;
    size_t g;
    size_t i;

    if (pairs == NULL || group_count == NULL || n == 0) {
        if (group_count != NULL) {
            *group_count = 0;
        }
        return NULL;
    }

    groups = malloc(n * sizeof *groups);
    if (groups == NULL) {
        *group_count = 0;
        return NULL;
    }

    g = 0;
    for (i = 0; i < n; i++) {
        size_t j;
        for (j = 0; j < g; j++) {
            if (groups[j].key == pairs[i].key) {
                break;
            }
        }
        if (j == g) {
            const char **vals = malloc(n * sizeof *vals);
            if (vals == NULL) {
                free_groups(groups, g);
                *group_count = 0;
                return NULL;
            }
            groups[g].key = pairs[i].key;
            groups[g].values = vals;
            groups[g].count = 0;
            g++;
        }
        groups[j].values[groups[j].count] = pairs[i].value;
        groups[j].count++;
    }

    *group_count = g;
    return groups;
}

int main(void)
{
    const Pair pairs[] = {
        { 1, "Jake" },
        { 2, "Bob" },
        { 1, "Cara" },
        { 3, "Sam" },
        { 2, "Lisa" }
    };
    size_t n = sizeof pairs / sizeof pairs[0];
    size_t group_count = 0;
    size_t i;
    size_t j;
    Group *groups;

    groups = sort_on_occurrence(pairs, n, &group_count);
    if (groups == NULL) {
        fprintf(stderr, "Failed to sort tuples\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < group_count; i++) {
        printf("(%d", groups[i].key);
        for (j = 0; j < groups[i].count; j++) {
            printf(", %s", groups[i].values[j]);
        }
        printf(", %zu)\n", groups[i].count);
    }

    free_groups(groups, group_count);
    return EXIT_SUCCESS;
}