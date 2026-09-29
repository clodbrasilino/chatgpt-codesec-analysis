#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NestedList {
    int value;
    bool is_integer;
    struct NestedList **children;
    int child_count;
} NestedList;

NestedList *create_integer_node(int value) {
    NestedList *node = (NestedList *)malloc(sizeof(NestedList));
    if (!node) {
        return NULL;
    }
    node->value = value;
    node->is_integer = true;
    node->children = NULL;
    node->child_count = 0;
    return node;
}

NestedList *create_list_node(NestedList **children, int child_count) {
    NestedList *node = (NestedList *)malloc(sizeof(NestedList));
    if (!node) {
        return NULL;
    }
    node->value = 0;
    node->is_integer = false;
    node->children = children;
    node->child_count = child_count;
    return node;
}

void free_nested_list(NestedList *list) {
    if (!list) {
        return;
    }
    if (!list->is_integer) {
        for (int i = 0; i < list->child_count; i++) {
            free_nested_list(list->children[i]);
        }
        free(list->children);
    }
    free(list);
}

bool is_subset_helper(NestedList *subset, NestedList *superset, bool *found_match) {
    if (subset->is_integer && superset->is_integer) {
        if (subset->value == superset->value) {
            *found_match = true;
            return true;
        }
        return false;
    }
    
    /* Possible weaknesses found:
     *  Assuming that condition 'subset->is_integer!=superset->is_integer' is not redundant
     */
    if (subset->is_integer != superset->is_integer) {
        /* Possible weaknesses found:
         *  Assuming that condition 'subset->is_integer' is not redundant
         *  Condition '!superset->is_integer' is always true [knownConditionTrueFalse]
         *  Condition '!superset->is_integer' is always true
         */
        if (subset->is_integer && !superset->is_integer) {
            for (int i = 0; i < superset->child_count; i++) {
                bool match = false;
                if (is_subset_helper(subset, superset->children[i], &match)) {
                    if (match) {
                        *found_match = true;
                        return true;
                    }
                }
            }
            return false;
        }
        return false;
    }
    
    /* Possible weaknesses found:
     *  Assuming that condition '!subset->is_integer' is not redundant
     *  Condition '!superset->is_integer' is always true [knownConditionTrueFalse]
     *  Condition '!superset->is_integer' is always true
     */
    if (!subset->is_integer && !superset->is_integer) {
        if (subset->child_count > superset->child_count) {
            return false;
        }
        
        bool *used = (bool *)calloc(superset->child_count, sizeof(bool));
        if (!used) {
            return false;
        }
        
        for (int i = 0; i < subset->child_count; i++) {
            bool element_found = false;
            for (int j = 0; j < superset->child_count; j++) {
                if (used[j]) {
                    continue;
                }
                bool match = false;
                if (is_subset_helper(subset->children[i], superset->children[j], &match)) {
                    if (match) {
                        used[j] = true;
                        element_found = true;
                        break;
                    }
                }
            }
            if (!element_found) {
                free(used);
                return false;
            }
        }
        free(used);
        *found_match = true;
        return true;
    }
    
    return false;
}

bool is_subset(NestedList *subset, NestedList *superset) {
    if (!subset && !superset) {
        return true;
    }
    if (!subset || !superset) {
        return false;
    }
    bool found_match = false;
    return is_subset_helper(subset, superset, &found_match);
}

int main(void) {
    NestedList *int1 = create_integer_node(1);
    NestedList *int2 = create_integer_node(2);
    NestedList *int3 = create_integer_node(3);
    NestedList *int4 = create_integer_node(1);
    
    NestedList *list1_children[] = {int1, int2};
    NestedList *list1 = create_list_node(list1_children, 2);
    
    NestedList *list2_children[] = {int4, int3};
    NestedList *list2 = create_list_node(list2_children, 2);
    
    NestedList *superset_children[] = {list1, list2};
    NestedList *superset = create_list_node(superset_children, 2);
    
    NestedList *subset_int1 = create_integer_node(1);
    NestedList *subset_int2 = create_integer_node(3);
    
    NestedList *subset_children[] = {subset_int1, subset_int2};
    NestedList *subset = create_list_node(subset_children, 2);
    
    if (is_subset(subset, superset)) {
        printf("Subset\n");
    } else {
        printf("Not subset\n");
    }
    
    free_nested_list(subset);
    free_nested_list(superset);
    
    return 0;
}