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
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    Node *head = NULL;
    head = append_node(head, 10);
    head = append_node(head, 20);
    head = append_node(head, 30);
    head = append_node(head, 40);
    head = append_node(head, 50);

    size_t n = 2;
    Node *nth_node = select_nth(head, n);
    if (nth_node != NULL) {
        printf("Item at index %zu is %d\n", n, nth_node->data);
    } else {
        printf("Index %zu is out of bounds\n", n);
    }

    n = 10;
    nth_node = select_nth(head, n);
    if (nth_node != NULL) {
        printf("Item at index %zu is %d\n", n, nth_node->data);
    } else {
        printf("Index %zu is out of bounds\n", n);
    }

    free_list(head);
    return 0;
}