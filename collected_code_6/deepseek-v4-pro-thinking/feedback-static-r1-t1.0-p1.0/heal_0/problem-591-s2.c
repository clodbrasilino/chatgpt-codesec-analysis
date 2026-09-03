#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *node = malloc(sizeof(*node));
    if (node != NULL) {
        node->data = data;
        node->next = NULL;
    }
    return node;
}

void interchange_first_last(Node *head) {
    if (head == NULL || head->next == NULL) {
        return;
    }
    Node *last = head;
    while (last->next != NULL) {
        last = last->next;
    }
    int temp = head->data;
    head->data = last->data;
    last->data = temp;
}

void print_list(const Node *head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

int main(void) {
    Node *head = create_node(10);
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    head->next = create_node(20);
    if (head->next == NULL) {
        free(head);
        return EXIT_FAILURE;
    }
    head->next->next = create_node(30);
    if (head->next->next == NULL) {
        free(head->next);
        free(head);
        return EXIT_FAILURE;
    }
    head->next->next->next = create_node(40);
    if (head->next->next->next == NULL) {
        free(head->next->next);
        free(head->next);
        free(head);
        return EXIT_FAILURE;
    }

    print_list(head);
    interchange_first_last(head);
    print_list(head);

    free_list(head);
    return 0;
}