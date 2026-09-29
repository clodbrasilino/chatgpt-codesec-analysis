#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

int count_sublists(Node *head, int element) {
    int count = 0;
    Node *current = head;
    while (current != NULL) {
        if (current->data == element) {
            count++;
        }
        current = current->next;
    }
    return count;
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

void append_node(Node **head_ref, int data) {
    Node *new_node = create_node(data);
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    Node *last = *head_ref;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
    Node *head = NULL;
    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 2);
    append_node(&head, 4);
    append_node(&head, 2);

    int target = 2;
    int result = count_sublists(head, target);
    printf("%d\n", result);

    free_list(head);
    return 0;
}