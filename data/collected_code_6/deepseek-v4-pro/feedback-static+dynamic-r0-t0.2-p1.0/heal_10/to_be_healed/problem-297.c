#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NestedList {
    int is_integer;
    int value;
    struct NestedList **list;
    int list_size;
} NestedList;

NestedList *create_integer(int value) {
    NestedList *node = (NestedList *)malloc(sizeof(NestedList));
    if (node == NULL) {
        return NULL;
    }
    node->is_integer = 1;
    node->value = value;
    node->list = NULL;
    node->list_size = 0;
    return node;
}

NestedList *create_list(NestedList **items, int size) {
    NestedList *node = (NestedList *)malloc(sizeof(NestedList));
    if (node == NULL) {
        return NULL;
    }
    node->is_integer = 0;
    node->value = 0;
    node->list = items;
    node->list_size = size;
    return node;
}

void free_nested_list(NestedList *node) {
    if (node == NULL) {
        return;
    }
    if (!node->is_integer) {
        if (node->list != NULL) {
            for (int i = 0; i < node->list_size; i++) {
                free_nested_list(node->list[i]);
                node->list[i] = NULL;
            }
            /* Possible weaknesses found:
             * ASan: attempting
             */
            free(node->list);
            node->list = NULL;
        }
    }
    free(node);
}

int *flatten(NestedList *nested, int *result_size) {
    if (nested == NULL || result_size == NULL) {
        return NULL;
    }

    int capacity = 16;
    int size = 0;
    int *result = (int *)malloc(capacity * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    NestedList **stack = (NestedList **)malloc(capacity * sizeof(NestedList *));
    if (stack == NULL) {
        free(result);
        return NULL;
    }

    int stack_size = 0;
    int stack_capacity = capacity;
    stack[stack_size++] = nested;

    while (stack_size > 0) {
        NestedList *current = stack[--stack_size];

        if (current == NULL) {
            continue;
        }

        if (current->is_integer) {
            if (size >= capacity) {
                capacity *= 2;
                int *new_result = (int *)realloc(result, capacity * sizeof(int));
                if (new_result == NULL) {
                    free(result);
                    free(stack);
                    return NULL;
                }
                result = new_result;
            }
            result[size++] = current->value;
        } else {
            if (current->list_size == 0) {
                continue;
            }
            if (stack_size + current->list_size > stack_capacity) {
                while (stack_capacity < stack_size + current->list_size) {
                    stack_capacity *= 2;
                }
                NestedList **new_stack = (NestedList **)realloc(stack, stack_capacity * sizeof(NestedList *));
                if (new_stack == NULL) {
                    free(result);
                    free(stack);
                    return NULL;
                }
                stack = new_stack;
            }
            for (int i = current->list_size - 1; i >= 0; i--) {
                if (current->list[i] != NULL) {
                    stack[stack_size++] = current->list[i];
                }
            }
        }
    }

    free(stack);
    *result_size = size;
    return result;
}

int main(void) {
    NestedList *inner1 = create_integer(1);
    NestedList *inner2 = create_integer(2);
    NestedList *inner_list_items[] = {inner1, inner2};
    NestedList *inner_list = create_list(inner_list_items, 2);

    NestedList *outer1 = create_integer(3);
    NestedList *outer2 = create_integer(4);
    NestedList *outer_list_items[] = {inner_list, outer1, outer2};
    NestedList *outer_list = create_list(outer_list_items, 3);

    int result_size = 0;
    int *flat_result = flatten(outer_list, &result_size);

    if (flat_result != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("%d ", flat_result[i]);
        }
        printf("\n");
        free(flat_result);
    }

    free_nested_list(outer_list);
    return 0;
}