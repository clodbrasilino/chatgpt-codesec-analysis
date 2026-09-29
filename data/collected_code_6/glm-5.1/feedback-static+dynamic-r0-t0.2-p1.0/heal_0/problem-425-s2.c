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
        Node *temp = current;
        current = current->next;
        free(temp);
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

int main() {
    Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(2);

    int result = count_sublists(head, 2);
    printf("%d\n", result);

    return 0;
}