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
    size_t count;
    size_t capacity;
} Group;

typedef struct {
    Group *groups;
    size_t count;
    size_t capacity;
} GroupList;

GroupList* create_group_list() {
    GroupList *list = (GroupList*)malloc(sizeof(GroupList));
    if (!list) return NULL;
    list->count = 0;
    list->capacity = 4;
    list->groups = (Group*)malloc(list->capacity * sizeof(Group));
    if (!list->groups) {
        free(list);
        return NULL;
    }
    return list;
}

void free_group_list(GroupList *list) {
    if (!list) return;
    for (size_t i = 0; i < list->count; i++) {
        free(list->groups[i].values);
    }
    free(list->groups);
    free(list);
}

int add_to_group(GroupList *list, int first, int second) {
    if (!list) return -1;

    for (size_t i = 0; i < list->count; i++) {
        if (list->groups[i].key == second) {
            Group *g = &list->groups[i];
            if (g->count == g->capacity) {
                size_t new_cap = g->capacity * 2;
                int *new_vals = (int*)realloc(g->values, new_cap * sizeof(int));
                if (!new_vals) return -1;
                g->values = new_vals;
                g->capacity = new_cap;
            }
            g->values[g->count++] = first;
            return 0;
        }
    }

    if (list->count == list->capacity) {
        size_t new_cap = list->capacity * 2;
        Group *new_groups = (Group*)realloc(list->groups, new_cap * sizeof(Group));
        if (!new_groups) return -1;
        list->groups = new_groups;
        list->capacity = new_cap;
    }

    Group *g = &list->groups[list->count++];
    g->key = second;
    g->count = 1;
    g->capacity = 4;
    g->values = (int*)malloc(g->capacity * sizeof(int));
    if (!g->values) {
        list->count--;
        return -1;
    }
    g->values[0] = first;
    return 0;
}

GroupList* group_tuples(const Tuple *tuples, size_t num_tuples) {
    if (!tuples) return NULL;

    GroupList *list = create_group_list();
    if (!list) return NULL;

    for (size_t i = 0; i < num_tuples; i++) {
        if (add_to_group(list, tuples[i].first, tuples[i].second) != 0) {
            free_group_list(list);
            return NULL;
        }
    }

    return list;
}

int main(void) {
    Tuple tuples[] = {
        {1, 10},
        {2, 20},
        {3, 10},
        {4, 30},
        {5, 20}
    };
    size_t num_tuples = sizeof(tuples) / sizeof(tuples[0]);

    GroupList *grouped = group_tuples(tuples, num_tuples);
    if (!grouped) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < grouped->count; i++) {
        printf("Key %d: [", grouped->groups[i].key);
        for (size_t j = 0; j < grouped->groups[i].count; j++) {
            printf("%d%s", grouped->groups[i].values[j], 
                   (j < grouped->groups[i].count - 1) ? ", " : "");
        }
        printf("]\n");
    }

    free_group_list(grouped);
    return 0;
}