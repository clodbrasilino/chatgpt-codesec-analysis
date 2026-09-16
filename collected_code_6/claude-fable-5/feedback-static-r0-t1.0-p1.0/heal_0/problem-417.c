#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    int first;
    int *seconds;
    size_t count;
    size_t capacity;
} Group;

static int add_to_group(Group *g, int value)
{
    if (g->count == g->capacity) {
        size_t new_cap = (g->capacity == 0U) ? 4U : g->capacity * 2U;
        int *tmp = realloc(g->seconds, new_cap * sizeof(int));
        if (tmp == NULL) {
            return -1;
        }
        g->seconds = tmp;
        g->capacity = new_cap;
    }
    g->seconds[g->count] = value;
    g->count++;
    return 0;
}

static void free_groups(Group *groups, size_t count)
{
    size_t i;
    if (groups == NULL) {
        return;
    }
    for (i = 0U; i < count; i++) {
        free(groups[i].seconds);
        groups[i].seconds = NULL;
    }
    free(groups);
}

static Group *group_common_first(const Tuple *tuples, size_t n, size_t *out_count)
{
    Group *groups;
    size_t group_count = 0U;
    size_t i;
    size_t j;

    if ((tuples == NULL) || (out_count == NULL) || (n == 0U)) {
        return NULL;
    }

    groups = calloc(n, sizeof(Group));
    if (groups == NULL) {
        return NULL;
    }

    for (i = 0U; i < n; i++) {
        int found = 0;
        for (j = 0U; j < group_count; j++) {
            if (groups[j].first == tuples[i].first) {
                if (add_to_group(&groups[j], tuples[i].second) != 0) {
                    free_groups(groups, group_count);
                    return NULL;
                }
                found = 1;
                break;
            }
        }
        if (found == 0) {
            groups[group_count].first = tuples[i].first;
            groups[group_count].seconds = NULL;
            groups[group_count].count = 0U;
            groups[group_count].capacity = 0U;
            if (add_to_group(&groups[group_count], tuples[i].second) != 0) {
                free_groups(groups, group_count);
                return NULL;
            }
            group_count++;
        }
    }

    *out_count = group_count;
    return groups;
}

static void print_groups(const Group *groups, size_t count)
{
    size_t i;
    size_t j;

    if (groups == NULL) {
        return;
    }

    for (i = 0U; i < count; i++) {
        if (printf("(%d", groups[i].first) < 0) {
            return;
        }
        for (j = 0U; j < groups[i].count; j++) {
            if (printf(", %d", groups[i].seconds[j]) < 0) {
                return;
            }
        }
        if (printf(")\n") < 0) {
            return;
        }
    }
}

int main(void)
{
    Tuple tuples[] = {
        {1, 10},
        {2, 20},
        {1, 30},
        {3, 40},
        {2, 50},
        {1, 60}
    };
    size_t n = sizeof(tuples) / sizeof(tuples[0]);
    size_t group_count = 0U;
    Group *groups;

    groups = group_common_first(tuples, n, &group_count);
    if (groups == NULL) {
        (void)fprintf(stderr, "Failed to group tuples\n");
        return EXIT_FAILURE;
    }

    print_groups(groups, group_count);
    free_groups(groups, group_count);

    return EXIT_SUCCESS;
}