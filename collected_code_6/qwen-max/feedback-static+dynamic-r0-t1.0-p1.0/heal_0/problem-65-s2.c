#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} Node;

Node* create_node(int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

int list_sum(Node *head) {
    if (head == NULL) {
        return 0;
    }
    return head->value + list_sum(head->next);
}

int main() {
    Node *head = create_node(1);
    Node *second = create_node(2);
    Node *third = create_node(3);

    head->next = second;
    second->next = third;

    printf("Sum of the linked list: %d\n", list_sum(head));

    free(head);
    free(second);
    free(third);

    return 0;
}