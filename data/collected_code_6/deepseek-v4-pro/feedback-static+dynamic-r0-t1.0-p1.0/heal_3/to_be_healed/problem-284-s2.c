#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char *data;
    struct node *next;
} node_t;

int all_items_equal(node_t *head, const char *target) {
    if (target == NULL) {
        return 0;
    }
    
    node_t *current = head;
    while (current != NULL) {
        if (current->data == NULL || strcmp(current->data, target) != 0) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}

node_t *create_node(const char *str) {
    node_t *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return NULL;
    }
    
    if (str == NULL) {
        free(new_node);
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    
    new_node->data = malloc(len + 1);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(new_node->data, str, len + 1);
    new_node->next = NULL;
    return new_node;
}

void free_list(node_t *head) {
    node_t *current = head;
    while (current != NULL) {
        node_t *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

int main(void) {
    node_t *head = create_node("apple");
    if (head == NULL) {
        return 1;
    }
    head->next = create_node("apple");
    if (head->next == NULL) {
        free_list(head);
        return 1;
    }
    head->next->next = create_node("apple");
    if (head->next->next == NULL) {
        free_list(head);
        return 1;
    }
    
    printf("Test 1: %d\n", all_items_equal(head, "apple"));
    printf("Test 2: %d\n", all_items_equal(head, "banana"));
    
    free_list(head);
    
    node_t *empty = NULL;
    printf("Test 3: %d\n", all_items_equal(empty, "apple"));
    printf("Test 4: %d\n", all_items_equal(empty, NULL));
    
    node_t *mixed = create_node("apple");
    if (mixed == NULL) {
        return 1;
    }
    mixed->next = create_node("banana");
    if (mixed->next == NULL) {
        free_list(mixed);
        return 1;
    }
    mixed->next->next = create_node("apple");
    if (mixed->next->next == NULL) {
        free_list(mixed);
        return 1;
    }
    
    printf("Test 5: %d\n", all_items_equal(mixed, "apple"));
    
    free_list(mixed);
    
    return 0;
}