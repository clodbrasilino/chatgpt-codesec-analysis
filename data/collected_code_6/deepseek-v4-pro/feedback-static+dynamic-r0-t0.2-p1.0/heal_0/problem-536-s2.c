#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node **head, int data) {
    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return;
    }
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

int select_nth_item(Node *head, int n) {
    if (head == NULL || n < 1) {
        return -1;
    }
    Node *current = head;
    int count = 1;
    while (current != NULL && count < n) {
        current = current->next;
        count++;
    }
    if (current == NULL) {
        return -1;
    }
    return current->data;
}

int main(void) {
    Node *head = NULL;
    append_node(&head, 10);
    append_node(&head, 20);
    append_node(&head, 30);
    append_node(&head, 40);
    append_node(&head, 50);

    int result = select_nth_item(head, 3);
    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("Item not found\n");
    }

    free_list(head);
    return 0;
}