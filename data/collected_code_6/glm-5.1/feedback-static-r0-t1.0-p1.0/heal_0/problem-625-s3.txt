#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* create_node(int data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Node* append_node(Node *head, int data) {
    Node *new_node = create_node(data);
    if (head == NULL) {
        return new_node;
    }
    Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return head;
}

Node* interchange_first_last(Node *head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    Node *last = head;
    Node *prev = NULL;

    while (last->next != NULL) {
        prev = last;
        last = last->next;
    }

    if (prev == head) {
        head->next = NULL;
        last->next = head;
        return last;
    }

    last->next = head->next;
    prev->next = head;
    head->next = NULL;

    return last;
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_list(Node *head) {
    Node *current = head;
    Node *next_node;
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}

int main(void) {
    Node *head = NULL;

    head = append_node(head, 1);
    head = append_node(head, 2);
    head = append_node(head, 3);
    head = append_node(head, 4);
    head = append_node(head, 5);

    print_list(head);

    head = interchange_first_last(head);

    print_list(head);

    free_list(head);

    return 0;
}