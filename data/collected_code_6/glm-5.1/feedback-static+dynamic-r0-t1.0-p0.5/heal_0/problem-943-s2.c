#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

Node *merge_lists(Node *l1, Node *l2) {
    Node dummy;
    dummy.next = NULL;
    Node *tail = &dummy;

    while (l1 != NULL && l2 != NULL) {
        if (l1->data <= l2->data) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    if (l1 != NULL) {
        tail->next = l1;
    } else {
        tail->next = l2;
    }

    return dummy.next;
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
    Node *l1 = create_node(1);
    l1->next = create_node(3);
    l1->next->next = create_node(5);

    Node *l2 = create_node(2);
    l2->next = create_node(4);
    l2->next->next = create_node(6);

    Node *merged = merge_lists(l1, l2);

    Node *current = merged;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    free_list(merged);

    return 0;
}