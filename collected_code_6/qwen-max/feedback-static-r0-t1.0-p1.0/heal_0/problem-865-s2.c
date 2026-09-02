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

void append_to_list(Node **head, int value) {
    if (*head == NULL) {
        *head = create_node(value);
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = create_node(value);
    }
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

void print_value(void *value) {
    printf("%d ", *(int *)value);
}

void map_list(Node *head, void (*func)(void *)) {
    while (head != NULL) {
        func(&head->value);
        head = head->next;
    }
}

void print_n_times(Node *head, int n) {
    for (int i = 0; i < n; ++i) {
        map_list(head, print_value);
    }
}

int main() {
    Node *list = NULL;
    append_to_list(&list, 1);
    append_to_list(&list, 2);
    append_to_list(&list, 3);

    int times = 3;
    print_n_times(list, times);

    free_list(list);
    return 0;
}