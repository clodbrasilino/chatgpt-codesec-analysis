#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* create_node(const char *data) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = malloc(strlen(data) + 1);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    strcpy(new_node->data, data);
    new_node->next = NULL;
    return new_node;
}

int insert_at_beginning(Node **head, const char *prefix) {
    if (head == NULL || prefix == NULL) {
        return -1;
    }
    
    Node *current = *head;
    size_t prefix_len = strlen(prefix);
    
    while (current != NULL) {
        size_t new_len = strlen(current->data) + prefix_len + 1;
        char *new_data = malloc(new_len);
        if (new_data == NULL) {
            return -1;
        }
        strcpy(new_data, prefix);
        strcat(new_data, current->data);
        free(current->data);
        current->data = new_data;
        current = current->next;
    }
    return 0;
}

int add_node(Node **head, const char *data) {
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