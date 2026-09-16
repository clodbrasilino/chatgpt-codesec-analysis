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

typedef struct {
    Group *groups;
    size_t count;
    size_t capacity;
} GroupList;

static void free_group_list(GroupList *list)
{
    size_t i;

    if (list == NULL) {
        return;
    }
    if (list->groups != NULL) {
        for (i = 0; i < list->count; i++) {
            free(list->groups[i].values);
            list->groups[i].values = NULL;
        }
        free(list->groups);
        list->groups = NULL;
    }
    list->count = 0;
    list->capacity = 0;
}

static Group *find_group(GroupList *list, int key)
{
    size_t i;

    for (i = 0; i < list->count; i++) {
        if (list->groups[i].key == key) {
            return &list->groups[i];
        }
    }
    return NULL;
}

static int add_group(GroupList *list, int key, Group **out)
{
    Group *tmp;
    size_t new_capacity;

    if (list->count == list->capacity) {
        new_capacity = (list->capacity == 0) ? 4 : list->capacity * 2;
        if (new_capacity < list->capacity) {
            return -1;
        }
        tmp = realloc(list->groups, new_capacity * sizeof(Group));
        if (tmp == NULL) {
            return -1;
        }
        list->groups = tmp;
        list->capacity = new_capacity;
    }
    list->groups[list->count].key = key;
    list->groups[list->count].values = NULL;
    list->groups[list->count].count = 0;
    list->groups[list->count].capacity = 0;
    *out = &list->groups[list->count];
    list->count++;
    return 0;
}

static int add_value(Group *group, int value)
{
    int *tmp;
    size_t new_capacity;

    if (group->count == group->capacity) {
        new_capacity = (group->capacity == 0) ? 4 : group->capacity * 2;
        if (new_capacity < group->capacity) {
            return -1;
        }
        tmp = realloc(group->values, new_capacity * sizeof(int));
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

static int group_by_second(const Pair *pairs, size_t n, GroupList *result)
{
    size_t i;
    Group *g;

    if (pairs == NULL && n > 0) {
        return -1;
    }
    if (result == NULL) {
        return -1;
    }
    result->groups = NULL;
    result->count = 0;
    result->capacity = 0;

    for (i = 0; i < n; i++) {
        g = find_group(result, pairs[i].second);
        if (g == NULL) {
            if (add_group(result, pairs[i].second, &g) != 0) {
                free_group_list(result);
                return -1;
            }
        }
        if (add_value(g, pairs[i].first) != 0) {
            free_group_list(result);
            return -1;
        }
    }
    return 0;
}

static void print_groups(const GroupList *list)
{
    size_t i;
    size_t j;

    printf("{");
    for (i = 0; i < list->count; i++) {
        printf("%d: [", list->groups[i].key);
        for (j = 0; j < list->groups[i].count; j++) {
            printf("%d", list->groups[i].values[j]);
            if (j + 1 < list->groups[i].count) {
                printf(", ");
            }
        }
        printf("]");
        if (i + 1 < list->count) {
            printf(", ");
        }
    }
    printf("}\n");
}

int main(void)
{
    Pair pairs[] = {
        {1, 3}, {2, 3}, {3, 1}, {4, 2}, {5, 1}, {6, 2}, {7, 3}
    };
    size_t n = sizeof(pairs) / sizeof(pairs[0]);
    GroupList result;

    if (group_by_second(pairs, n, &result) != 0) {
        fprintf(stderr, "Error: failed to group pairs\n");
        return EXIT_FAILURE;
    }

    print_groups(&result);
    free_group_list(&result);

    return EXIT_SUCCESS;
}