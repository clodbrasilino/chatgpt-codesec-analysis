#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* create_node(int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

void iterate_pairs(Node *head) {
    Node *current = head;
    while (current != NULL && current->next != NULL) {
        printf("(%d, %d)\n", current->value, current->next->value);
        current = current->next;
    }
}

int main() {
    Node *head = create_node(1);
    Node *second = create_node(2);
    Node *third = create_node(3);
    Node *fourth = create_node(4);

    if (head == NULL || second == NULL || third == NULL || fourth == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    head->next = second;
    second->next = third;
    third->next = fourth;

    iterate_pairs(head);

    free_list(head);
    return 0;
}