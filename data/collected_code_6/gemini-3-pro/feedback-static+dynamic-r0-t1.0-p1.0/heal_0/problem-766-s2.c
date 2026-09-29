#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void iterate_pairs(Node* head) {
    if (head == NULL) {
        return;
    }

    Node* current = head;
    while (current->next != NULL) {
        printf("(%d, %d)\n", current->data, current->next->data);
        current = current->next;
    }
}

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node* head) {
    Node* current = head;
    Node* next_node;
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}

int main(void) {
    Node* head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(4);
    head->next->next->next->next = create_node(5);

    iterate_pairs(head);

    free_list(head);

    return EXIT_SUCCESS;
}