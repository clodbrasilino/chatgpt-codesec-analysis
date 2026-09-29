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
    if (head == NULL || result == NULL || n <= 0) {
        return 0;
    }
    Node *current = head;
    int index = 1;
    while (current != NULL) {
        if (index == n) {
            *result = current->data;
            return 1;
        }
        current = current->next;
        index++;
    }
    return 0;
}

int main(void) {
    Node *list = NULL;
    int values[] = {10, 20, 30, 40, 50};
    int count = sizeof(values) / sizeof(values[0]);
    int i;
    for (i = 0; i < count; i++) {
        append_node(&list, values[i]);
    }
    int nth_values[] = {1, 3, 5, 7};
    int nth_count = sizeof(nth_values) / sizeof(nth_values[0]);
    for (i = 0; i < nth_count; i++) {
        int result;
        if (select_nth_item(list, nth_values[i], &result)) {
            printf("Item at position %d: %d\n", nth_values[i], result);
        } else {
            printf("Position %d not found\n", nth_values[i]);
        }
    }
    free_list(list);
    return 0;
}