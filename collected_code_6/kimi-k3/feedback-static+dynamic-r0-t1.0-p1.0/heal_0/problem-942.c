#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

int contains(const Node *head, int value) {
    const Node *current = head;
    while (current != NULL) {
        if (current->data == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

Node *create_node(int value) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    Node *head = create_node(10);
    if (head == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    head->next = create_node(20);
    if (head->next == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_list(head);
        return EXIT_FAILURE;
    }
    
    head->next->next = create_node(30);
    if (head->next->next == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_list(head);
        return EXIT_FAILURE;
    }
    
    int target = 20;
    if (contains(head, target)) {
        printf("%d is present in the list\n", target);
    } else {
        printf("%d is not present in the list\n", target);
    }
    
    target = 40;
    if (contains(head, target)) {
        printf("%d is present in the list\n", target);
    } else {
        printf("%d is not present in the list\n", target);
    }
    
    free_list(head);
    return EXIT_SUCCESS;
}