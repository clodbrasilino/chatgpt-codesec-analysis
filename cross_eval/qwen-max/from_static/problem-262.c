#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node* head) {
    Node* current = head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

Node* split_list(const Node* head, int length) {
    if (head == NULL || length <= 0) {
        return NULL;
    }

    const Node* current = head;
    Node* previous = NULL;

    for (int i = 1; i < length && current != NULL; i++) {
        previous = (Node*)current;
        current = current->next;
    }

    if (current == NULL) {
        return NULL;
    }

    Node* second_part_head = (Node*)current;
    if (previous != NULL) {
        previous->next = NULL;
    }

    return second_part_head;
}

int main() {
    Node* head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(4);

    int split_length = 2;
    Node* second_part_head = split_list(head, split_length);

    for (Node* current = head; current != NULL; current = current->next) {
        printf("%d ", current->value);
    }
    printf("\n");

    for (Node* current = second_part_head; current != NULL; current = current->next) {
        printf("%d ", current->value);
    }
    printf("\n");

    free_list(head);
    if (second_part_head != NULL) {
        free_list(second_part_head);
    }

    return 0;
}