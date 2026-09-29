#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *split_list(Node *head, int k, Node **second_part) {
    if (k < 0) {
        *second_part = NULL;
        return NULL;
    }

    if (k == 0) {
        *second_part = head;
        return NULL;
    }

    if (head == NULL) {
        *second_part = NULL;
        return NULL;
    }

    Node *current = head;
    int count = 1;

    while (current->next != NULL && count < k) {
        current = current->next;
        count++;
    }

    *second_part = current->next;
    current->next = NULL;

    return head;
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
    while (current != NULL) {
        Node *next = current->next;
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

    Node *second_part = NULL;
    Node *first_part = split_list(head, 3, &second_part);

    print_list(first_part);
    print_list(second_part);

    free_list(first_part);
    free_list(second_part);

    return 0;
}