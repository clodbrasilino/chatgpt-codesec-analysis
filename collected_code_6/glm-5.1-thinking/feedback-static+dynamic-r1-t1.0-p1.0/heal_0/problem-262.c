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

void split_list(Node *source, int k, Node **front, Node **back) {
    if (front == NULL || back == NULL) {
        return;
    }
    if (source == NULL || k <= 0) {
        *front = NULL;
        *back = source;
        return;
    }
    *front = source;
    Node *current = source;
    int count = 1;
    while (current->next != NULL && count < k) {
        current = current->next;
        count++;
    }
    *back = current->next;
    current->next = NULL;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(4);
    head->next->next->next->next = create_node(5);

    Node *part1 = NULL;
    Node *part2 = NULL;

    split_list(head, 2, &part1, &part2);

    print_list(part1);
    print_list(part2);

    free_list(part1);
    free_list(part2);

    return 0;
}