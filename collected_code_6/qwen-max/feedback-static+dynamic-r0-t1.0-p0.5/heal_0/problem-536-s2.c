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

int get_nth_value(Node *head, int n) {
    Node *current = head;
    int index = 0;
    while (current != NULL && index < n) {
        current = current->next;
        index++;
    }
    if (current == NULL) {
        return -1; // Indicate not found
    }
    return current->value;
}

int main() {
    Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(4);

    int n = 2;
    int nth_value = get_nth_value(head, n);
    if (nth_value != -1) {
        printf("The %dth item is: %d\n", n + 1, nth_value);
    } else {
        printf("The %dth item does not exist.\n", n + 1);
    }

    free_list(head);
    return 0;
}