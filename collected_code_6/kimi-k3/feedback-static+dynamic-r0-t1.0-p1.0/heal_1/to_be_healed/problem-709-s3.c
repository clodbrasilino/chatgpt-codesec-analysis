#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define INITIAL_CAPACITY 16

typedef struct {
    int key;
    int value;
} Tuple;

typedef struct {
    int *data;
    size_t count;
    size_t capacity;
} IntArray;

typedef struct {
    int value;
    IntArray keys;
} ValueGroup;

typedef struct {
    ValueGroup *groups;
    size_t count;
    size_t capacity;
} GroupList;

static void int_array_init(IntArray *arr) {
    if (arr == NULL) {
        return;
    }
    arr->data = NULL;
    arr->count = 0;
    arr->capacity = 0;
}

static void int_array_free(IntArray *arr) {
    if (arr == NULL) {
        return;
    }
    free(arr->data);
    arr->data = NULL;
    arr->count = 0;
    arr->capacity = 0;
}

static int int_array_contains(const IntArray *arr, int key) {
    size_t i;
    if (arr == NULL || arr->data == NULL) {
        return 0;
    }
    for (i = 0; i < arr->count; i++) {
        if (arr->data[i] == key) {
            return 1;
        }
    }
    return 0;
}

static int int_array_add(IntArray *arr, int key) {
    int *new_data;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
     */
    size_t new_capacity;
    
    if (arr == NULL) {
        return -1;
    }
    
    if (int_array_contains(arr, key)) {
        return 0;
    }
    
    if (arr->count >= arr->capacity) {
        new_capacity = (arr->capacity == 0) ? INITIAL_CAPACITY : arr->capacity * 2;
        if (new_capacity < arr->capacity) {
            return -1;
        }
        new_data = realloc(arr->data, new_capacity * sizeof(int));
        if (new_data == NULL) {
            return -1;
        }
        arr->data = new_data;
        arr->capacity = new_capacity;
    }
    
    arr->data[arr->count] = key;
    arr->count++;
    return 0;
}

static void group_list_init(GroupList *list) {
    if (list == NULL) {
        return;
    }
    list->groups = NULL;
    list->count = 0;
    list->capacity = 0;
}

static void group_list_free(GroupList *list) {
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;
    if (list == NULL) {
        return;
    }
    if (list->groups != NULL) {
        for (i = 0; i < list->count; i++) {
            int_array_free(&list->groups[i].keys);
        }
        free(list->groups);
    }
    list->groups = NULL;
    list->count = 0;
    list->capacity = 0;
}

static ValueGroup *group_list_find(GroupList *list, int value) {
    size_t i;
    if (list == NULL || list->groups == NULL) {
        return NULL;
    }
    for (i = 0; i < list->count; i++) {
        if (list->groups[i].value == value) {
            return &list->groups[i];
        }
    }
    return NULL;
}

static ValueGroup *group_list_add_value(GroupList *list, int value) {
    ValueGroup *new_groups;
    ValueGroup *group;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
     */
    size_t new_capacity;
    
    if (list == NULL) {
        return NULL;
    }
    
    if (list->count >= list->capacity) {
        new_capacity = (list->capacity == 0) ? INITIAL_CAPACITY : list->capacity * 2;
        if (new_capacity < list->capacity) {
            return NULL;
        }
        new_groups = realloc(list->groups, new_capacity * sizeof(ValueGroup));
        if (new_groups == NULL) {
            return NULL;
        }
        list->groups = new_groups;
        list->capacity = new_capacity;
    }
    
    group = &list->groups[list->count];
    group->value = value;
    int_array_init(&group->keys);
    list->count++;
    
    return group;
}

static int count_unique_keys_per_value(const Tuple *tuples, size_t tuple_count, GroupList *result) {
    size_t i;
    ValueGroup *group;
    
    if (result == NULL) {
        return -1;
    }
    
    group_list_init(result);
    
    if (tuples == NULL && tuple_count > 0) {
        return -1;
    }
    
    for (i = 0; i < tuple_count; i++) {
        group = group_list_find(result, tuples[i].value);
        if (group == NULL) {
            group = group_list_add_value(result, tuples[i].value);
            if (group == NULL) {
                group_list_free(result);
                return -1;
            }
        }
        
        if (int_array_add(&group->keys, tuples[i].key) != 0) {
            group_list_free(result);
            return -1;
        }
    }
    
    return 0;
}

static void print_results(const GroupList *list) {
    size_t i;
    if (list == NULL) {
        return;
    }
    for (i = 0; i < list->count; i++) {
        printf("Value %d: %zu unique key(s)\n", 
               list->groups[i].value, 
               list->groups[i].keys.count);
    }
}

int main(void) {
    Tuple tuples[] = {
        {1, 100},
        {2, 100},
        {3, 200},
        {1, 100},
        {4, 200},
        {5, 300},
        {2, 100},
        {6, 300}
    };
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    GroupList result;
    int status;
    
    status = count_unique_keys_per_value(tuples, tuple_count, &result);
    if (status != 0) {
        fprintf(stderr, "Error: Failed to process tuples\n");
        return EXIT_FAILURE;
    }
    
    print_results(&result);
    group_list_free(&result);
    
    return EXIT_SUCCESS;
}