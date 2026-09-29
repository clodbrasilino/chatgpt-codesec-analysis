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

Node *remove_even(Node *head) {
    Node **indirect = &head;
    Node *current;
    while (*indirect != NULL) {
        current = *indirect;
        if (current->data % 2 == 0) {
            *indirect = current->next;
            free(current);
        } else {
            indirect = &current->next;
        }
    }
    return head;
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_list(Node *head) {
    Node *current = head;
    Node *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(4);
    head->next->next->next->next = create_node(5);

    print_list(head);
    head = remove_even(head);
    print_list(head);
    free_list(head);

    return 0;
}