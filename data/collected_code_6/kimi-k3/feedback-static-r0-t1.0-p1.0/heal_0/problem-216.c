#include <stdio.h>
#include <stdlib.h>

typedef struct NestedList {
    int *data;
    int size;
    int is_integer;
    struct NestedList **children;
    int child_count;
} NestedList;

NestedList* create_integer(int value) {
    NestedList *list = (NestedList*)malloc(sizeof(NestedList));
    if (list == NULL) {
        return NULL;
    }
    list->data = (int*)malloc(sizeof(int));
    if (list->data == NULL) {
        free(list);
        return NULL;
    }
    *list->data = value;
    list->size = 1;
    list->is_integer = 1;
    list->children = NULL;
    list->child_count = 0;
    return list;
}

NestedList* create_list(int capacity) {
    NestedList *list = (NestedList*)malloc(sizeof(NestedList));
    if (list == NULL) {
        return NULL;
    }
    list->data = NULL;
    list->size = 0;
    list->is_integer = 0;
    list->children = (NestedList**)malloc(sizeof(NestedList*) * capacity);
    if (list->children == NULL) {
        free(list);
        return NULL;
    }
    list->child_count = 0;
    return list;
}

void add_child(NestedList *parent, NestedList *child) {
    if (parent == NULL || child == NULL || parent->is_integer) {
        return;
    }
    parent->children[parent->child_count] = child;
    parent->child_count++;
}

void free_nested_list(NestedList *list) {
    if (list == NULL) {
        return;
    }
    if (list->data != NULL) {
        free(list->data);
    }
    if (list->children != NULL) {
        int i;
        for (i = 0; i < list->child_count; i++) {
            free_nested_list(list->children[i]);
        }
        free(list->children);
    }
    free(list);
}

int is_equal(NestedList *a, NestedList *b) {
    if (a == NULL || b == NULL) {
        return 0;
    }
    if (a->is_integer != b->is_integer) {
        return 0;
    }
    if (a->is_integer) {
        return *a->data == *b->data;
    }
    if (a->child_count != b->child_count) {
        return 0;
    }
    int i;
    for (i = 0; i < a->child_count; i++) {
        if (!is_equal(a->children[i], b->children[i])) {
            return 0;
        }
    }
    return 1;
}

int is_subset(NestedList *subset, NestedList *superset) {
    if (subset == NULL || superset == NULL) {
        return 0;
    }
    if (subset->is_integer && superset->is_integer) {
        return *subset->data == *superset->data;
    }
    if (subset->is_integer && !superset->is_integer) {
        int i;
        for (i = 0; i < superset->child_count; i++) {
            if (is_subset(subset, superset->children[i])) {
                return 1;
            }
        }
        return 0;
    }
    if (!subset->is_integer && superset->is_integer) {
        return 0;
    }
    int i;
    for (i = 0; i < subset->child_count; i++) {
        int found = 0;
        int j;
        for (j = 0; j < superset->child_count; j++) {
            if (is_subset(subset->children[i], superset->children[j])) {
                found = 1;
                break;
            }
        }
        if (!found) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    NestedList *list1 = create_list(5);
    NestedList *list2 = create_list(5);
    
    NestedList *int1 = create_integer(1);
    NestedList *int2 = create_integer(2);
    NestedList *int3 = create_integer(3);
    NestedList *int4 = create_integer(4);
    
    NestedList *nested1 = create_list(3);
    NestedList *int5 = create_integer(5);
    NestedList *int6 = create_integer(6);
    
    if (list1 == NULL || list2 == NULL || int1 == NULL || 
        int2 == NULL || int3 == NULL || int4 == NULL ||
        nested1 == NULL || int5 == NULL || int6 == NULL) {
        free_nested_list(list1);
        free_nested_list(list2);
        free_nested_list(int1);
        free_nested_list(int2);
        free_nested_list(int3);
        free_nested_list(int4);
        free_nested_list(nested1);
        free_nested_list(int5);
        free_nested_list(int6);
        return 1;
    }
    
    add_child(nested1, int5);
    add_child(nested1, int6);
    
    add_child(list1, int1);
    add_child(list1, int2);
    add_child(list1, nested1);
    
    add_child(list2, int3);
    add_child(list2, int4);
    
    int result = is_subset(list2, list1);
    printf("Is subset: %d\n", result);
    
    free_nested_list(list1);
    free_nested_list(list2);
    
    return 0;
}