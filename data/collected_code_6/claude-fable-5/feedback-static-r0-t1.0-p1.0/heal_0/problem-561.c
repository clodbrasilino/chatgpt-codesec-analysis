#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

typedef struct {
    int key;
    int *values;
    size_t count;
    size_t capacity;
} Group;

static int add_value(Group *group, int value)
{
    if (group->count == group->capacity) {
        size_t new_capacity = (group->capacity == 0) ? 4 : group->capacity * 2;
        int *tmp = realloc(group->values, new_capacity * sizeof(int));
        if (tmp == NULL) {
            return -1;
        }
        group->values = tmp;
        group->capacity = new_capacity;
    }
    group->values[group->count] = value;
    group->count++;
    return 0;
}

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

static Group *assign_pairs(const Pair *pairs, size_t pair_count, size_t *out_group_count)
{
    Group *groups = NULL;
    size_t group_count = 0;
    size_t group_capacity = 0;
    size_t i;
    size_t j;

    if (pairs == NULL || out_group_count == NULL) {
        return NULL;
    }

    for (i = 0; i < pair_count; i++) {
        size_t found_index = group_count;
        for (j = 0; j < group_count; j++) {
            if (groups[j].key == pairs[i].first) {
                found_index = j;
                break;
            }
        }
        if (found_index == group_count) {
            if (group_count == group_capacity) {
                size_t new_capacity = (group_capacity == 0) ? 4 : group_capacity * 2;
                Group *tmp = realloc(groups, new_capacity * sizeof(Group));
                if (tmp == NULL) {
                    free_groups(groups, group_count);
                    return NULL;
                }
                groups = tmp;
                group_capacity = new_capacity;
            }
            groups[group_count].key = pairs[i].first;
            groups[group_count].values = NULL;
            groups[group_count].count = 0;
            groups[group_count].capacity = 0;
            group_count++;
        }
        if (add_value(&groups[found_index], pairs[i].second) != 0) {
            free_groups(groups, group_count);
            return NULL;
        }
    }

    *out_group_count = group_count;
    return groups;
}

static void print_groups(const Group *groups, size_t group_count)
{
    size_t i;
    size_t j;
    for (i = 0; i < group_count; i++) {
        printf("%d: [", groups[i].key);
        for (j = 0; j < groups[i].count; j++) {
            printf("%d", groups[i].values[j]);
            if (j + 1 < groups[i].count) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

int main(void)
{
    Pair pairs[] = {
        {5, 4},
        {8, 2},
        {5, 3},
        {5, 8},
        {8, 4}
    };
    size_t pair_count = sizeof(pairs) / sizeof(pairs[0]);
    size_t group_count = 0;
    Group *groups = assign_pairs(pairs, pair_count, &group_count);

    if (groups == NULL) {
        fprintf(stderr, "Failed to assign pairs\n");
        return EXIT_FAILURE;
    }

    print_groups(groups, group_count);
    free_groups(groups, group_count);
    return EXIT_SUCCESS;
}