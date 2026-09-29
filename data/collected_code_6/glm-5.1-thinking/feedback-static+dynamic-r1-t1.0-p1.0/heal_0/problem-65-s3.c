#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

int list_sum(Node *head) {
    if (head == NULL) {
        return 0;
    }
    return head->data + list_sum(head->next);
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

    head->next = create_node(20);
    if (head->next == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }

    head->next->next = create_node(30);
    if (head->next->next == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }

    int total = list_sum(head);
    printf("%d\n", total);

    free_list(head);
    return EXIT_SUCCESS;
}