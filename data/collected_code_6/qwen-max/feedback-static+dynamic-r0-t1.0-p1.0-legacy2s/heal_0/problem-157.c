#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int value;
    int count;
    struct Node *next;
} Node;

Node* insert(Node *head, int value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return head;
    new_node->value = value;
    new_node->count = 1;
    new_node->next = NULL;

    if (head == NULL) {
        return new_node;
    }

    Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return head;
}

Node* add_count(Node *head, int value) {
    Node *current = head;
    while (current != NULL) {
        if (current->value == value) {
            current->count++;
            return head;
        }
        current = current->next;
    }
    return insert(head, value);
}

Node* run_length_encode(const int *input, size_t length) {
    Node *head = NULL;
    for (size_t i = 0; i < length; ++i) {
        if (i > 0 && input[i] != input[i - 1]) {
            head = add_count(head, input[i]);
        } else if (i == 0) {
            head = insert(head, input[i]);
        }
    }
    return head;
}

void print_encoded_list(Node *head) {
    while (head != NULL) {
        printf("%d %d ", head->value, head->count);
        head = head->next;
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

int main() {
    int arr[] = {2, 2, 3, 5, 5, 5, 4, 8, 8, 10, 10, 10, 10};
    size_t length = sizeof(arr) / sizeof(arr[0]);

    Node *encoded_list = run_length_encode(arr, length);
    print_encoded_list(encoded_list);

    free_list(encoded_list);
    return 0;
}