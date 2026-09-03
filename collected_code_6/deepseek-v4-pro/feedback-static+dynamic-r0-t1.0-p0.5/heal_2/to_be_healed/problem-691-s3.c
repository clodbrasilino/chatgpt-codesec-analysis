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

static void init_group_list(GroupList *list) {
    list->groups = NULL;
    list->count = 0;
    list->capacity = 0;
}

static int find_group(GroupList *list, int key) {
    for (int i = 0; i < list->count; i++) {
        if (list->groups[i].key == key) {
            return i;
        }
    }
    return -1;
}

static int add_group(GroupList *list, int key) {
    if (list->count == list->capacity) {
        int new_capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        Group *new_groups = realloc(list->groups, new_capacity * sizeof(Group));
        if (new_groups == NULL) {
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

static int add_value_to_group(Group *group, int value) {
    if (group->count == group->capacity) {
        int new_capacity = group->capacity == 0 ? 4 : group->capacity * 2;
        int *new_values = realloc(group->values, new_capacity * sizeof(int));
        if (new_values == NULL) {
            return -1;
        }
        group->values = new_values;
        group->capacity = new_capacity;
    }
    
    group->values[group->count] = value;
    group->count++;
    return 0;
}

static void free_group_list(GroupList *list) {
    for (int i = 0; i < list->count; i++) {
        free(list->groups[i].values);
    }
    free(list->groups);
    list->groups = NULL;
    list->count = 0;
    list->capacity = 0;
}

static GroupList group_by_second(Tuple *tuples, int tuple_count) {
    GroupList result;
    init_group_list(&result);
    
    for (int i = 0; i < tuple_count; i++) {
        int group_index = find_group(&result, tuples[i].second);
        
        if (group_index == -1) {
            group_index = add_group(&result, tuples[i].second);
            if (group_index == -1) {
                free_group_list(&result);
                return result;
            }
        }
        
        if (add_value_to_group(&result.groups[group_index], tuples[i].first) == -1) {
            free_group_list(&result);
            return result;
        }
    }
    
    return result;
}

static void print_grouped_result(GroupList *list) {
    for (int i = 0; i < list->count; i++) {
        printf("Key %d: ", list->groups[i].key);
        for (int j = 0; j < list->groups[i].count; j++) {
            printf("%d", list->groups[i].values[j]);
            if (j < list->groups[i].count - 1) {
                printf(", ");
            }
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
    
    /* Possible weaknesses found:
     *  Assignment 'tuple_count=(int)(sizeof(tuples)/sizeof(tuples[0]))', assigned value is 8
     */
    int tuple_count = (int)(sizeof(tuples) / sizeof(tuples[0]));
    
    /* Possible weaknesses found:
     *  Condition 'tuple_count==0' is always false
     *  Condition 'tuple_count==0' is always false [knownConditionTrueFalse]
     */
    if (tuple_count == 0) {
        return 0;
    }
    
    GroupList grouped = group_by_second(tuples, tuple_count);
    
    if (grouped.groups == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    print_grouped_result(&grouped);
    
    free_group_list(&grouped);
    
    return 0;
}