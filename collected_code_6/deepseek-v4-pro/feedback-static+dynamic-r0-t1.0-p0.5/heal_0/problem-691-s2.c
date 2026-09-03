#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    int key;
    int *values;
    int count;
    int capacity;
} Group;

typedef struct {
    Group *groups;
    int count;
    int capacity;
} GroupList;

static int find_group(GroupList *list, int key) {
    int i;
    for (i = 0; i < list->count; i++) {
        if (list->groups[i].key == key) {
            return i;
        }
    }
    return -1;
}

static int add_to_group(Group *group, int value) {
    if (group->count >= group->capacity) {
        int new_capacity = group->capacity == 0 ? 4 : group->capacity * 2;
        int *new_values = (int *)realloc(group->values, new_capacity * sizeof(int));
        if (new_values == NULL) {
            return 0;
        }
        group->values = new_values;
        group->capacity = new_capacity;
    }
    group->values[group->count++] = value;
    return 1;
}

static int add_group(GroupList *list, int key, int value) {
    if (list->count >= list->capacity) {
        int new_capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        Group *new_groups = (Group *)realloc(list->groups, new_capacity * sizeof(Group));
        if (new_groups == NULL) {
            return 0;
        }
        list->groups = new_groups;
        list->capacity = new_capacity;
    }
    list->groups[list->count].key = key;
    list->groups[list->count].values = NULL;
    list->groups[list->count].count = 0;
    list->groups[list->count].capacity = 0;
    if (!add_to_group(&list->groups[list->count], value)) {
        return 0;
    }
    list->count++;
    return 1;
}

GroupList *group_by_second(Tuple *tuples, int tuple_count) {
    GroupList *result;
    int i;

    if (tuples == NULL || tuple_count <= 0) {
        return NULL;
    }

    result = (GroupList *)malloc(sizeof(GroupList));
    if (result == NULL) {
        return NULL;
    }
    result->groups = NULL;
    result->count = 0;
    result->capacity = 0;

    for (i = 0; i < tuple_count; i++) {
        int idx = find_group(result, tuples[i].second);
        if (idx >= 0) {
            if (!add_to_group(&result->groups[idx], tuples[i].first)) {
                int j;
                for (j = 0; j < result->count; j++) {
                    free(result->groups[j].values);
                }
                free(result->groups);
                free(result);
                return NULL;
            }
        } else {
            if (!add_group(result, tuples[i].second, tuples[i].first)) {
                int j;
                for (j = 0; j < result->count; j++) {
                    free(result->groups[j].values);
                }
                free(result->groups);
                free(result);
                return NULL;
            }
        }
    }

    return result;
}

void free_group_list(GroupList *list) {
    int i;
    if (list == NULL) {
        return;
    }
    for (i = 0; i < list->count; i++) {
        free(list->groups[i].values);
    }
    free(list->groups);
    free(list);
}

int main(void) {
    Tuple tuples[] = {
        {1, 10},
        {2, 20},
        {3, 10},
        {4, 30},
        {5, 20},
        {6, 10}
    };
    int tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    GroupList *result = group_by_second(tuples, tuple_count);
    int i, j;

    if (result == NULL) {
        fprintf(stderr, "Failed to group tuples\n");
        return 1;
    }

    for (i = 0; i < result->count; i++) {
        printf("Key %d: ", result->groups[i].key);
        for (j = 0; j < result->groups[i].count; j++) {
            printf("%d ", result->groups[i].values[j]);
        }
        printf("\n");
    }

    free_group_list(result);
    return 0;
}