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

void free_list(Node *head) {
    Node *current = head;
    Node *next_node;
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}

int main() {
    Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(2);
    head->next->next->next->next = create_node(4);

    int target = 2;
    int result = count_sublists(head, target);
    printf("%d\n", result);

    free_list(head);

    return 0;
}