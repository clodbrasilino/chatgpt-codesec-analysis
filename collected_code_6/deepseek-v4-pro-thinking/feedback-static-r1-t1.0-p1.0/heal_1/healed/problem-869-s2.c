#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int *data;
    int size;
    struct Node *next;
} Node;

Node *create_sublist(const int *values, int size) {
    Node *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->data = malloc(sizeof(int) * size);
    if (node->data == NULL) {
        free(node);
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        node->data[i] = values[i];
    }
    node->size = size;
    node->next = NULL;
    return node;
}

void remove_sublists_outside_range(Node **head, int low, int high) {
    if (head == NULL || low > high) {
        return;
    }

    Node **current = head;
    while (*current != NULL) {
        Node *node = *current;
        if (node->size < low || node->size > high) {
            *current = node->next;
            free(node->data);
            free(node);
        } else {
            current = &node->next;
        }
    }
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *next = head->next;
        free(head->data);
        free(head);
        head = next;
    }
}

void print_list(Node *head) {
    while (head != NULL) {
        printf("[");
        for (int i = 0; i < head->size; i++) {
            printf("%d", head->data[i]);
            if (i < head->size - 1) {
                printf(", ");
            }
        }
        printf("] ");
        head = head->next;
    }
    printf("\n");
}

int main(void) {
    const int arr1[] = {1, 2};
    const int arr2[] = {1, 2, 3, 4, 5};
    const int arr3[] = {1, 2, 3};
    const int arr4[] = {4, 5, 6, 7};

    Node *head = create_sublist(arr1, 2);
    if (head == NULL) {
        return 1;
    }
    head->next = create_sublist(arr2, 5);
    if (head->next == NULL) {
        free_list(head);
        return 1;
    }
    head->next->next = create_sublist(arr3, 3);
    if (head->next->next == NULL) {
        free_list(head);
        return 1;
    }
    head->next->next->next = create_sublist(arr4, 4);
    if (head->next->next->next == NULL) {
        free_list(head);
        return 1;
    }

    print_list(head);
    remove_sublists_outside_range(&head, 3, 4);
    print_list(head);

    free_list(head);
    return 0;
}