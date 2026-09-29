#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void insert_before_each(Node **head, int value) {
    if (*head == NULL) {
        return;
    }

    Node *current = *head;
    *head = create_node(value);
    (*head)->next = current;

    while (current->next != NULL) {
        Node *temp = create_node(value);
        temp->next = current->next;
        current->next = temp;
        current = temp->next;
    }
}

void print_list(Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);

    printf("Original list: ");
    print_list(head);

    insert_before_each(&head, 0);

    printf("List after insertion: ");
    print_list(head);

    free_list(head);
    return 0;
}