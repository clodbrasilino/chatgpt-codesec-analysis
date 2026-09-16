#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

bool list_contains(Node *head, int value) {
    Node *current = head;
    while (current != NULL) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
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
        return EXIT_FAILURE;
    }
    
    Node *second = create_node(20);
    if (second == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }
    head->next = second;
    
    Node *third = create_node(30);
    if (third == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }
    second->next = third;
    
    int search_value = 20;
    if (list_contains(head, search_value)) {
        printf("Value %d found in the list.\n", search_value);
    } else {
        printf("Value %d not found in the list.\n", search_value);
    }
    
    free_list(head);
    
    return EXIT_SUCCESS;
}