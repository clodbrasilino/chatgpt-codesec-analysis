#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* create_node(int data) {
    Node *node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

Node* select_nth(Node *head, size_t n) {
    if (head == NULL) {
        return NULL;
    }
    Node *current = head;
    size_t count = 0;
    while (current != NULL && count < n) {
        current = current->next;
        count++;
    }
    return current;
}

void free_list(Node *head) {
    Node *current = head;
    Node *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    Node *head = create_node(10);
    head->next = create_node(20);
    head->next->next = create_node(30);
    head->next->next->next = create_node(40);

    size_t n = 2;
    Node *result = select_nth(head, n);
    if (result != NULL) {
        printf("Item at index %zu is %d\n", n, result->data);
    } else {
        printf("Index %zu out of bounds\n", n);
    }

    n = 5;
    result = select_nth(head, n);
    if (result != NULL) {
        printf("Item at index %zu is %d\n", n, result->data);
    } else {
        printf("Index %zu out of bounds\n", n);
    }

    free_list(head);
    return 0;
}