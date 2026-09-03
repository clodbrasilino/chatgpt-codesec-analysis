#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

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

void append_node(Node **head, int data) {
    Node *new_node = create_node(data);
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

int list_length(Node *head) {
    int length = 0;
    Node *current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

Node *rotate_right(Node *head, int k) {
    if (head == NULL || head->next == NULL || k == 0) {
        return head;
    }

    int length = list_length(head);
    k = k % length;
    if (k == 0) {
        return head;
    }

    Node *slow = head;
    Node *fast = head;

    for (int i = 0; i < k; i++) {
        fast = fast->next;
    }

    while (fast->next != NULL) {
        slow = slow->next;
        fast = fast->next;
    }

    Node *new_head = slow->next;
    slow->next = NULL;
    fast->next = head;

    return new_head;
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
    Node *head = NULL;
    int values[] = {1, 2, 3, 4, 5};
    int size = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < size; i++) {
        append_node(&head, values[i]);
    }

    printf("Original list: ");
    print_list(head);

    int k = 2;
    head = rotate_right(head, k);

    printf("Rotated list by %d: ", k);
    print_list(head);

    free_list(head);
    return 0;
}