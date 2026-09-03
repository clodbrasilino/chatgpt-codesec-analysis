#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node **head, int data) {
    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return;
    }
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

int select_nth_item(Node *head, int n, int *result) {
    if (head == NULL || result == NULL || n < 1) {
        return 0;
    }
    Node *current = head;
    int count = 1;
    while (current != NULL) {
        if (count == n) {
            *result = current->data;
            return 1;
        }
        current = current->next;
        count++;
    }
    return 0;
}

int main(void) {
    Node *list = NULL;
    int values[] = {10, 20, 30, 40, 50};
    size_t num_values = sizeof(values) / sizeof(values[0]);
    size_t i;

    for (i = 0; i < num_values; i++) {
        append_node(&list, values[i]);
    }

    int nth_value;
    int test_positions[] = {1, 3, 5, 6, 0};
    size_t num_tests = sizeof(test_positions) / sizeof(test_positions[0]);

    for (i = 0; i < num_tests; i++) {
        if (select_nth_item(list, test_positions[i], &nth_value)) {
            printf("Item at position %d: %d\n", test_positions[i], nth_value);
        } else {
            printf("Position %d not found\n", test_positions[i]);
        }
    }

    free_list(list);
    return 0;
}