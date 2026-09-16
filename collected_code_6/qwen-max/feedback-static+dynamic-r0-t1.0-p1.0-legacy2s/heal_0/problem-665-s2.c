#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* create_node(int value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void shift_first_to_end(Node **head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    Node *current = *head;
    Node *second = (*head)->next;
    Node *tail = *head;

    while (tail->next != NULL) {
        tail = tail->next;
    }

    *head = second;
    tail->next = current;
    current->next = NULL;
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);

    shift_first_to_end(&head);

    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");

    free_list(head);
    return 0;
}