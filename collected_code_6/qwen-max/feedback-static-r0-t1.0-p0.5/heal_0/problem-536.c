#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* create_node(int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
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

Node* select_nth_item(Node *head, int n) {
    if (n < 0) {
        return NULL;
    }
    Node *current = head;
    for (int i = 0; i < n && current != NULL; i++) {
        current = current->next;
    }
    return current;
}

int main() {
    Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(4);

    int n = 2;
    Node *nth_node = select_nth_item(head, n);
    if (nth_node != NULL) {
        printf("The %dth item is: %d\n", n + 1, nth_node->value);
    } else {
        printf("The %dth item does not exist.\n", n + 1);
    }

    free_list(head);
    return 0;
}