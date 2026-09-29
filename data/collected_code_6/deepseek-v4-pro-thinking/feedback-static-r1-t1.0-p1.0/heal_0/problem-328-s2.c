#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

Node *append_node(Node *head, int data) {
    Node *node = create_node(data);
    if (!head) {
        return node;
    }
    Node *current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = node;
    return head;
}

Node *rotate_left(Node *head, int k) {
    if (!head || k <= 0) {
        return head;
    }

    int length = 1;
    Node *tail = head;
    while (tail->next) {
        tail = tail->next;
        length++;
    }

    k %= length;
    if (k == 0) {
        return head;
    }

    Node *current = head;
    for (int i = 1; i < k; i++) {
        current = current->next;
    }

    Node *new_head = current->next;
    current->next = NULL;
    tail->next = head;
    return new_head;
}

void print_list(const Node *head) {
    const Node *current = head;
    while (current) {
        printf("%d", current->data);
        current = current->next;
        if (current) {
            printf(" -> ");
        }
    }
    printf("\n");
}

void free_list(Node *head) {
    Node *current = head;
    while (current) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    Node *head = NULL;
    int values[] = {1, 2, 3, 4, 5};
    int count = (int)(sizeof(values) / sizeof(values[0]));

    for (int i = 0; i < count; i++) {
        head = append_node(head, values[i]);
    }

    print_list(head);
    head = rotate_left(head, 2);
    print_list(head);

    free_list(head);
    return 0;
}