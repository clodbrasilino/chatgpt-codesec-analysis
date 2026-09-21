#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node *create_node(const char *str) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *data = (char *)malloc(len + 1);
    if (data == NULL) {
        free(new_node);
        return NULL;
    }
    
    if (len + 1 < len) {
        free(data);
        free(new_node);
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(data, str, len + 1);
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void insert_at_beginning(Node **head, const char *str) {
    Node *new_node = create_node(str);
    if (new_node == NULL) {
        return;
    }
    new_node->next = *head;
    *head = new_node;
}

void prepend_to_all(Node *head, const char *prefix) {
    Node *current = head;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t prefix_len = strlen(prefix);
    
    while (current != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t data_len = strlen(current->data);
        
        if (prefix_len > SIZE_MAX - data_len || prefix_len + data_len > SIZE_MAX - 1) {
            return;
        }
        
        size_t new_len = prefix_len + data_len + 1;
        
        if (new_len <= prefix_len || new_len <= data_len) {
            return;
        }
        
        char *new_str = (char *)malloc(new_len);
        if (new_str == NULL) {
            return;
        }
        
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_str, prefix, prefix_len);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_str + prefix_len, current->data, data_len + 1);
        
        free(current->data);
        current->data = new_str;
        current = current->next;
    }
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

int main(void) {
    Node *list = NULL;
    
    insert_at_beginning(&list, "world");
    insert_at_beginning(&list, "there");
    insert_at_beginning(&list, "hello");
    
    printf("Original list:\n");
    print_list(list);
    
    prepend_to_all(list, "say_");
    
    printf("\nModified list:\n");
    print_list(list);
    
    free_list(list);
    
    return 0;
}