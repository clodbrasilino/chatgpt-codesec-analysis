#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Node *alternate_list(Node *head) {
    if (head == NULL) {
        return NULL;
    }

    Node *new_head = create_node(head->data);
    Node *current = new_head;
    Node *src = head->next;

    int take = 0;
    while (src != NULL) {
        if (take) {
            current->next = create_node(src->data);
            current = current->next;
        }
        take = !take;
        src = src->next;
    }

    return new_head;
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

int main(void) {
    Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(4);
    head->next->next->next->next = create_node(5);

    Node *alt = alternate_list(head);

    Node *temp = alt;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");

    free_list(head);
    free_list(alt);

    return 0;
}