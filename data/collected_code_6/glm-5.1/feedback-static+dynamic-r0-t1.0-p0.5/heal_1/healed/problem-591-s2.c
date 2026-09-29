#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *interchange_first_last(Node *head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    Node *prev = NULL;
    Node *curr = head;

    while (curr->next != NULL) {
        prev = curr;
        curr = curr->next;
    }

    Node *last = curr;
    Node *first = head;

    if (prev != NULL) {
        prev->next = first;
    }

    last->next = first->next;
    first->next = NULL;

    return last;
}

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

void print_list(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

int main(void) {
    Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(4);

    print_list(head);

    head = interchange_first_last(head);

    print_list(head);

    free_list(head);

    return 0;
}