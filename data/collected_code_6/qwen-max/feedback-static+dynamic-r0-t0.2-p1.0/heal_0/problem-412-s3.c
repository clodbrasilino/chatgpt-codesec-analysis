#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* create_node(int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

Node* remove_odds(Node *head) {
    Node *dummy = create_node(0);
    dummy->next = head;
    Node *prev = dummy;
    Node *current = head;

    while (current != NULL) {
        if (current->value % 2 != 0) {
            prev->next = current->next;
            free(current);
            current = prev->next;
        } else {
            prev = current;
            current = current->next;
        }
    }

    Node *new_head = dummy->next;
    free(dummy);
    return new_head;
}

int main() {
    Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(4);

    head = remove_odds(head);

    for (Node *current = head; current != NULL; current = current->next) {
        printf("%d ", current->value);
    }
    printf("\n");

    free_list(head);
    return 0;
}