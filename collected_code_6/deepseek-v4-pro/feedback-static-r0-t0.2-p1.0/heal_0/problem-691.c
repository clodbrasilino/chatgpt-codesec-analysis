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
    for (int i = 0; i < list->count; i++) {
        if (list->groups[i].key == key) {
            return i;
        }
    }
    return -1;
}

static int add_group(GroupList *list, int key) {
    if (list->count >= list->capacity) {
        int new_capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        Group *new_groups = realloc(list->groups, new_capacity * sizeof(Group));
        if (!new_groups) {
            return -1;
        }
        list->groups = new_groups;
        list->capacity = new_capacity;
    }
    
    list->groups[list->count].key = key;
    list->groups[list->count].values = NULL;
    list->groups[list->count].count = 0;
    list->groups[list->count].capacity = 0;
    list->count++;
    
    return list->count - 1;
}

static int add_value(Group *group, int value) {
    if (group->count >= group->capacity) {
        int new_capacity = group->capacity == 0 ? 4 : group->capacity * 2;
        int *new_values = realloc(group->values, new_capacity * sizeof(int));
        if (!new_values) {
            return -1;
        }
        group->values = new_values;
        group->capacity = new_capacity;
    }
    
    group->values[group->count] = value;
    group->count++;
    
    return 0;
}

GroupList *group_by_second(Tuple *tuples, int tuple_count) {
    if (!tuples || tuple_count <= 0) {
        return NULL;
    }
    
    GroupList *result = malloc(sizeof(GroupList));
    if (!result) {
        return NULL;
    }
    
    result->groups = NULL;
    result->count = 0;
    result->capacity = 0;
    
    for (int i = 0; i < tuple_count; i++) {
        int group_index = find_group(result, tuples[i].second);
        
        if (group_index == -1) {
            group_index = add_group(result, tuples[i].second);
            if (group_index == -1) {
                for (int j = 0; j < result->count; j++) {
                    free(result->groups[j].values);
                }
                free(result->groups);
                free(result);
                return NULL;
            }
        }
        
        if (add_value(&result->groups[group_index], tuples[i].first) != 0) {
            for (int j = 0; j < result->count; j++) {
                free(result->groups[j].values);
            }
            free(result->groups);
            free(result);
            return NULL;
        }
    }
    
    return result;
}

void free_group_list(GroupList *list) {
    if (!list) {
        return;
    }
    
    for (int i = 0; i < list->count; i++) {
        free(list->groups[i].values);
    }
    
    free(list->groups);
    free(list);
}

void print_group_list(GroupList *list) {
    if (!list) {
        printf("NULL\n");
        return;
    }
    
    for (int i = 0; i < list->count; i++) {
        printf("Key %d: ", list->groups[i].key);
        for (int j = 0; j < list->groups[i].count; j++) {
            printf("%d ", list->groups[i].values[j]);
        }
        printf("\n");
    }
}

int main(void) {
    Tuple tuples[] = {
        {1, 10},
        {2, 20},
        {3, 10},
        {4, 30},
        {5, 20},
        {6, 10},
        {7, 40},
        {8, 30}
    };
    
    int tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    
    GroupList *result = group_by_second(tuples, tuple_count);
    
    if (result) {
        print_group_list(result);
        free_group_list(result);
    } else {
        printf("Failed to group tuples\n");
    }
    
    return 0;
}