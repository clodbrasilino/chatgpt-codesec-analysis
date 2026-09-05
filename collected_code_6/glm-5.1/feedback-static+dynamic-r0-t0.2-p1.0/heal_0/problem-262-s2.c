#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

Node *split_list(Node *head, int k, Node **second_part) {
    if (head == NULL || k <= 0) {
        *second_part = head;
        return NULL;
    }

    Node *current = head;
    int count = 1;
    while (current->next != NULL && count < k) {
        current = current->next;
        count++;
    }

    *second_part = current->next;
    current->next = NULL;

    return head;
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
    Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(4);
    head->next->next->next->next = create_node(5);

    Node *second_part = NULL;
    Node *first_part = split_list(head, 2, &second_part);

    printf("First part: ");
    Node *curr = first_part;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");

    printf("Second part: ");
    curr = second_part;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");

    free_list(first_part);
    free_list(second_part);

    return 0;
}