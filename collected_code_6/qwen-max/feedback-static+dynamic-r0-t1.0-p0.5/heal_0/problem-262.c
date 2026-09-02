#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node **head, int data) {
    Node *new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void print_list(Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void split_list(Node *head, int length, Node **first_part, Node **second_part) {
    if (head == NULL || length <= 0) {
        *first_part = NULL;
        *second_part = head;
        return;
    }

    Node *current = head;
    for (int i = 1; i < length && current->next != NULL; i++) {
        current = current->next;
    }

    *first_part = head;
    *second_part = current->next;
    current->next = NULL;
}

int main() {
    Node *head = NULL;
    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 4);
    append_node(&head, 5);

    printf("Original list: ");
    print_list(head);

    Node *first_part = NULL;
    Node *second_part = NULL;
    split_list(head, 3, &first_part, &second_part);

    printf("First part: ");
    print_list(first_part);

    printf("Second part: ");
    print_list(second_part);

    return 0;
}