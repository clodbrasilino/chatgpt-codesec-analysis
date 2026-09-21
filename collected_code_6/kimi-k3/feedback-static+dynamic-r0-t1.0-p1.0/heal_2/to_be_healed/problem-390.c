#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* create_node(const char *data) {
    if (data == NULL) {
        return NULL;
    }
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(data);
    new_node->data = malloc(len + 1);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(new_node->data, data, len + 1);
    new_node->next = NULL;
    return new_node;
}

int insert_at_beginning(Node **head, const char *prefix) {
    if (head == NULL || prefix == NULL) {
        return -1;
    }
    
    Node *current = *head;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t prefix_len = strlen(prefix);
    
    while (current != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t current_len = strlen(current->data);
        size_t new_len = current_len + prefix_len + 1;
        char *new_data = malloc(new_len);
        if (new_data == NULL) {
            return -1;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_data, prefix, prefix_len);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_data + prefix_len, current->data, current_len + 1);
        free(current->data);
        current->data = new_data;
        current = current->next;
    }
    return 0;
}

int add_node(Node **head, const char *data) {
    if (head == NULL || data == NULL) {
        return -1;
    }
    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return -1;
    }
    new_node->next = *head;
    *head = new_node;
    return 0;
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

void free_list(Node **head) {
    if (head == NULL) {
        return;
    }
    Node *current = *head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
    *head = NULL;
}

int main(void) {
    Node *head = NULL;
    
    if (add_node(&head, "world") != 0) {
        fprintf(stderr, "Failed to add node\n");
        free_list(&head);
        return EXIT_FAILURE;
    }
    if (add_node(&head, "hello") != 0) {
        fprintf(stderr, "Failed to add node\n");
        free_list(&head);
        return EXIT_FAILURE;
    }
    if (add_node(&head, "test") != 0) {
        fprintf(stderr, "Failed to add node\n");
        free_list(&head);
        return EXIT_FAILURE;
    }
    
    printf("Before insertion:\n");
    print_list(head);
    
    if (insert_at_beginning(&head, "PREFIX_") != 0) {
        fprintf(stderr, "Failed to insert prefix\n");
        free_list(&head);
        return EXIT_FAILURE;
    }
    
    printf("\nAfter insertion:\n");
    print_list(head);
    
    free_list(&head);
    return EXIT_SUCCESS;
}