#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *interchange_first_and_last(Node *head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    Node *prev_last = NULL;
    Node *last = head;

    while (last->next != NULL) {
        prev_last = last;
        last = last->next;
    }

    if (head->next == last) {
        last->next = head;
        head->next = NULL;
        return last;
    }

    last->next = head->next;
    prev_last->next = head;
    head->next = NULL;

    return last;
}

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
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

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(4);
    head->next->next->next->next = create_node(5);

    head = interchange_first_and_last(head);
    print_list(head);

    free_list(head);

    return EXIT_SUCCESS;
}