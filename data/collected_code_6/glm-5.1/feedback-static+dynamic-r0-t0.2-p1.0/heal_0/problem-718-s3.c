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

Node *build_list(int *arr, int size) {
    if (size == 0) {
        return NULL;
    }
    Node *head = create_node(arr[0]);
    Node *current = head;
    for (int i = 1; i < size; i++) {
        current->next = create_node(arr[i]);
        current = current->next;
    }
    return head;
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
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int size = sizeof(arr) / sizeof(arr[0]);
    Node *original = build_list(arr, size);
    Node *alt = alternate_list(original);
    print_list(original);
    print_list(alt);
    free_list(original);
    free_list(alt);
    return 0;
}