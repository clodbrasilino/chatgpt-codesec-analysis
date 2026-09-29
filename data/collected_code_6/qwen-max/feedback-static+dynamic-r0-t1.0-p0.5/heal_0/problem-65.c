#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
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
    head->next = create_node(2);
    head->next->next = create_node(3);

    printf("Sum of the list: %d\n", list_sum(head));

    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}