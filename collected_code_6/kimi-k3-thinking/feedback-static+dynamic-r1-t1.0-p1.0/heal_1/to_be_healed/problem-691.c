#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    int key;
    int *items;
    size_t count;
    size_t capacity;
} Group;

static int find_group(const Group *groups, size_t group_count, int key, size_t *index)
{
    size_t i;

    for (i = 0; i < group_count; i++) {
        if (groups[i].key == key) {
            *index = i;
            return 1;
        }
    }
    return 0;
}

void free_groups(Group *groups, size_t group_count)
{
    size_t i;

    if (groups == NULL) {
        return;
    }

    for (i = 0; i < group_count; i++) {
        free(groups[i].items);
    }
    free(groups);
}

Group *group_by_second(const Tuple *tuples, size_t tuple_count, size_t *group_count)
{
    Group *groups = NULL;
    Group *tmp_groups = NULL;
    int *tmp_items = NULL;
    size_t index = 0;
    /* Possible weaknesses found:
     *  Variable 'new_capacity' is assigned a value that is never used. [unreadVariable]
     */
    size_t new_capacity = 0;
    size_t i;

    if (group_count == NULL) {
        return NULL;
    }
    *group_count = 0;

    if (tuples == NULL || tuple_count == 0) {
        return NULL;
    }

    for (i = 0; i < tuple_count; i++) {
        if (!find_group(groups, *group_count, tuples[i].second, &index)) {
            if (*group_count >= SIZE_MAX / sizeof(Group)) {
                free_groups(groups, *group_count);
                *group_count = 0;
                return NULL;
            }
            tmp_groups = (Group *)realloc(groups, (*group_count + 1) * sizeof(Group));
            if (tmp_groups == NULL) {
                free_groups(groups, *group_count);
                *group_count = 0;
                return NULL;
            }
            groups = tmp_groups;
            index = *group_count;
            groups[index].key = tuples[i].second;
            groups[index].items = NULL;
            groups[index].count = 0;
            groups[index].capacity = 0;
            *group_count += 1;
        }

        if (groups[index].count == groups[index].capacity) {
            if (groups[index].capacity == 0) {
                new_capacity = 4;
            } else {
                if (groups[index].capacity > SIZE_MAX / 2) {
                    free_groups(groups, *group_count);
                    *group_count = 0;
                    return NULL;
                }
                new_capacity = groups[index].capacity * 2;
            }
            if (new_capacity > SIZE_MAX / sizeof(int)) {
                free_groups(groups, *group_count);
                *group_count = 0;
                return NULL;
            }
            tmp_items = (int *)realloc(groups[index].items, new_capacity * sizeof(int));
            if (tmp_items == NULL) {
                free_groups(groups, *group_count);
                *group_count = 0;
                return NULL;
            }
            groups[index].items = tmp_items;
            groups[index].capacity = new_capacity;
        }

        groups[index].items[groups[index].count] = tuples[i].first;
        groups[index].count += 1;
    }

    return groups;
}

int main(void)
{
    Tuple tuples[] = {
        {1, 10},
        {2, 20},
        {3, 10},
        {4, 30},
        {5, 20},
        {6, 10},
        {7, 30}
    };
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    size_t group_count = 0;
    Group *groups = NULL;
    size_t i;
    size_t j;

    groups = group_by_second(tuples, tuple_count, &group_count);
    if (groups == NULL) {
        fprintf(stderr, "Error: failed to group tuples\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < group_count; i++) {
        printf("%d -> [", groups[i].key);
        for (j = 0; j < groups[i].count; j++) {
            printf("%d", groups[i].items[j]);
            if (j + 1 < groups[i].count) {
                printf(", ");
            }
        }
        printf("]\n");
    }

    free_groups(groups, group_count);

    return EXIT_SUCCESS;
}