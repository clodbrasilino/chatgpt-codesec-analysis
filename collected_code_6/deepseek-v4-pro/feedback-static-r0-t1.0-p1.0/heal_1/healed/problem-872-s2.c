#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NestedList {
    int value;
    bool is_integer;
    struct NestedList **list;
    int size;
} NestedList;

NestedList *create_integer(int value) {
    NestedList *node = (NestedList *)malloc(sizeof(NestedList));
    if (node == NULL) {
        return NULL;
    }
    node->value = value;
    node->is_integer = true;
    node->list = NULL;
    node->size = 0;
    return node;
}

NestedList *create_list(NestedList **items, int size) {
    NestedList *node = (NestedList *)malloc(sizeof(NestedList));
    if (node == NULL) {
        return NULL;
    }
    node->is_integer = false;
    node->value = 0;
    node->list = (NestedList **)malloc(sizeof(NestedList *) * size);
    if (node->list == NULL && size > 0) {
        free(node);
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        node->list[i] = items[i];
    }
    node->size = size;
    return node;
}

void free_nested_list(NestedList *node) {
    if (node == NULL) {
        return;
    }
    if (!node->is_integer) {
        for (int i = 0; i < node->size; i++) {
            free_nested_list(node->list[i]);
        }
        free(node->list);
    }
    free(node);
}

bool nested_list_contains_helper(NestedList *container, NestedList *target, bool *used) {
    if (container->is_integer && target->is_integer) {
        return container->value == target->value;
    }
    if (container->is_integer != target->is_integer) {
        return false;
    }
    if (container->size < target->size) {
        return false;
    }
    
    bool *used_copy = (bool *)malloc(sizeof(bool) * container->size);
    if (used_copy == NULL) {
        return false;
    }
    for (int i = 0; i < container->size; i++) {
        used_copy[i] = used[i];
    }
    
    for (int i = 0; i < target->size; i++) {
        bool found = false;
        for (int j = 0; j < container->size; j++) {
            if (!used_copy[j]) {
                bool *new_used = (bool *)malloc(sizeof(bool) * container->size);
                if (new_used == NULL) {
                    free(used_copy);
                    return false;
                }
                for (int k = 0; k < container->size; k++) {
                    new_used[k] = used_copy[k];
                }
                new_used[j] = true;
                
                if (nested_list_contains_helper(container->list[j], target->list[i], new_used)) {
                    bool *temp_used = (bool *)malloc(sizeof(bool) * container->size);
                    if (temp_used == NULL) {
                        free(new_used);
                        free(used_copy);
                        return false;
                    }
                    for (int k = 0; k < container->size; k++) {
                        temp_used[k] = new_used[k];
                    }
                    for (int k = 0; k < container->size; k++) {
                        used_copy[k] = temp_used[k];
                    }
                    free(temp_used);
                    free(new_used);
                    found = true;
                    break;
                }
                free(new_used);
            }
        }
        if (!found) {
            free(used_copy);
            return false;
        }
    }
    
    for (int i = 0; i < container->size; i++) {
        used[i] = used_copy[i];
    }
    free(used_copy);
    return true;
}

bool is_subset(NestedList *list1, NestedList *list2) {
    if (list1 == NULL || list2 == NULL) {
        return false;
    }
    
    bool *used = (bool *)calloc(list1->size, sizeof(bool));
    if (used == NULL) {
        return false;
    }
    
    bool result = nested_list_contains_helper(list1, list2, used);
    free(used);
    return result;
}

int main(void) {
    NestedList *n1 = create_integer(1);
    NestedList *n2 = create_integer(2);
    NestedList *n3 = create_integer(3);
    
    NestedList *inner_list1_items[] = {n1, n2};
    NestedList *inner_list1 = create_list(inner_list1_items, 2);
    
    NestedList *outer1_items[] = {inner_list1, n3};
    NestedList *outer1 = create_list(outer1_items, 2);
    
    NestedList *n5 = create_integer(1);
    NestedList *n6 = create_integer(2);
    
    NestedList *inner_list2_items[] = {n5, n6};
    NestedList *inner_list2 = create_list(inner_list2_items, 2);
    
    NestedList *outer2_items[] = {inner_list2};
    NestedList *outer2 = create_list(outer2_items, 1);
    
    if (is_subset(outer1, outer2)) {
        printf("outer2 is a subset of outer1\n");
    } else {
        printf("outer2 is not a subset of outer1\n");
    }
    
    free_nested_list(outer1);
    free_nested_list(outer2);
    
    return 0;
}