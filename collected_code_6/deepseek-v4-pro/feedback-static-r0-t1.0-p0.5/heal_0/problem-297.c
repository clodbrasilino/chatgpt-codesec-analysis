#include <stdio.h>
#include <stdlib.h>

typedef struct NestedList {
    int is_integer;
    int value;
    struct NestedList *list;
    struct NestedList *next;
} NestedList;

NestedList *create_integer(int value) {
    NestedList *node = (NestedList *)malloc(sizeof(NestedList));
    if (node == NULL) {
        return NULL;
    }
    node->is_integer = 1;
    node->value = value;
    node->list = NULL;
    node->next = NULL;
    return node;
}

NestedList *create_list(NestedList *list) {
    NestedList *node = (NestedList *)malloc(sizeof(NestedList));
    if (node == NULL) {
        return NULL;
    }
    node->is_integer = 0;
    node->value = 0;
    node->list = list;
    node->next = NULL;
    return node;
}

void append_node(NestedList **head, NestedList *node) {
    if (*head == NULL) {
        *head = node;
        return;
    }
    NestedList *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
}

void flatten_helper(NestedList *nested, NestedList **flat_head, NestedList **flat_tail) {
    if (nested == NULL) {
        return;
    }
    
    NestedList *current = nested;
    while (current != NULL) {
        if (current->is_integer) {
            NestedList *new_node = create_integer(current->value);
            if (new_node == NULL) {
                return;
            }
            if (*flat_head == NULL) {
                *flat_head = new_node;
                *flat_tail = new_node;
            } else {
                (*flat_tail)->next = new_node;
                *flat_tail = new_node;
            }
        } else {
            flatten_helper(current->list, flat_head, flat_tail);
        }
        current = current->next;
    }
}

NestedList *flatten(NestedList *nested) {
    NestedList *flat_head = NULL;
    NestedList *flat_tail = NULL;
    flatten_helper(nested, &flat_head, &flat_tail);
    return flat_head;
}

void free_nested_list(NestedList *node) {
    while (node != NULL) {
        NestedList *next = node->next;
        if (!node->is_integer) {
            free_nested_list(node->list);
        }
        free(node);
        node = next;
    }
}

void print_flat_list(NestedList *head) {
    NestedList *current = head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    NestedList *nested = NULL;
    NestedList *inner1 = NULL;
    NestedList *inner2 = NULL;
    NestedList *inner3 = NULL;
    NestedList *flat = NULL;
    
    append_node(&inner1, create_integer(1));
    append_node(&inner1, create_integer(2));
    
    append_node(&inner2, create_integer(3));
    
    append_node(&inner3, create_integer(4));
    append_node(&inner3, create_integer(5));
    
    append_node(&nested, create_list(inner1));
    append_node(&nested, create_integer(6));
    append_node(&nested, create_list(inner2));
    append_node(&nested, create_list(inner3));
    append_node(&nested, create_integer(7));
    
    flat = flatten(nested);
    print_flat_list(flat);
    
    free_nested_list(nested);
    free_nested_list(flat);
    
    return 0;
}