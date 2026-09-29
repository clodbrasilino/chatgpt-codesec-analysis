#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

const Node *get_nth_item(const Node *head, int n) {
    if (head == NULL || n < 0) {
        return NULL;
    }

    const Node *current = head;
    int count = 0;

    while (current != NULL && count < n) {
        current = current->next;
        count++;
    }

    return current;
}

Node *create_node(int data) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
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
    Node *head = create_node(10);
    head->next = create_node(20);
    head->next->next = create_node(30);

    const Node *item = get_nth_item(head, 1);
    if (item != NULL) {
        printf("%d\n", item->data);
    } else {
        printf("Item not found\n");
    }

    free_list(head);

    return 0;
}