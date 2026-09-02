#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int value;
    int count;
    struct Node *next;
} Node;

Node *create_node(int value, int count) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->value = value;
    node->count = count;
    node->next = NULL;
    return node;
}

void append_node(Node **head, int value, int count) {
    Node *new_node = create_node(value, count);
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

Node *run_length_encode(const int *input, int length) {
    if (input == NULL || length <= 0) {
        return NULL;
    }

    Node *head = NULL;
    int current_value = input[0];
    int current_count = 1;

    for (int i = 1; i < length; i++) {
        if (input[i] == current_value) {
            current_count++;
        } else {
            append_node(&head, current_value, current_count);
            current_value = input[i];
            current_count = 1;
        }
    }
    append_node(&head, current_value, current_count);
    return head;
}

void print_encoded_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("(%d,%d) ", current->value, current->count);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    int input[] = {1, 1, 1, 2, 2, 3, 3, 3, 3, 1};
    int length = sizeof(input) / sizeof(input[0]);

    Node *encoded = run_length_encode(input, length);
    if (encoded == NULL) {
        fprintf(stderr, "Encoding failed\n");
        return EXIT_FAILURE;
    }

    print_encoded_list(encoded);
    free_list(encoded);

    return EXIT_SUCCESS;
}