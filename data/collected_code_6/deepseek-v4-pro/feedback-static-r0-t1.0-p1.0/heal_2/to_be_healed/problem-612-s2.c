#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int *data;
    int size;
    struct Node *next;
} Node;

Node *create_node(const int *arr, int size) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) return NULL;
    node->data = (int *)malloc(sizeof(int) * size);
    if (!node->data) {
        free(node);
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        node->data[i] = arr[i];
    }
    node->size = size;
    node->next = NULL;
    return node;
}

void free_list(Node *head) {
    Node *cur = head;
    while (cur) {
        Node *next = cur->next;
        free(cur->data);
        free(cur);
        cur = next;
    }
}

int *merge_first_last(Node *head, int *out_size) {
    if (!head) {
        if (out_size) {
            *out_size = 0;
        }
        return NULL;
    }
    if (!out_size) {
        return NULL;
    }

    Node *first = head;
    Node *last = head;
    while (last->next) {
        last = last->next;
    }

    int total = first->size + last->size;
    if (total == 0) {
        *out_size = 0;
        return NULL;
    }

    int *result = (int *)malloc(sizeof(int) * total);
    if (!result) {
        *out_size = 0;
        return NULL;
    }

    int idx = 0;
    for (int i = 0; i < first->size; i++) {
        result[idx++] = first->data[i];
    }
    for (int i = 0; i < last->size; i++) {
        result[idx++] = last->data[i];
    }

    *out_size = total;
    return result;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'a1' can be declared as const array [constVariable]
     */
    int a1[] = {1, 2, 3};
    /* Possible weaknesses found:
     *  Variable 'a2' can be declared as const array [constVariable]
     */
    int a2[] = {4, 5};
    /* Possible weaknesses found:
     *  Variable 'a3' can be declared as const array [constVariable]
     */
    int a3[] = {6, 7, 8, 9};

    Node *head = create_node(a1, 3);
    if (!head) return 1;
    head->next = create_node(a2, 2);
    if (!head->next) {
        free_list(head);
        return 1;
    }
    head->next->next = create_node(a3, 4);
    if (!head->next->next) {
        free_list(head);
        return 1;
    }

    int merged_size = 0;
    int *merged = merge_first_last(head, &merged_size);
    if (merged) {
        for (int i = 0; i < merged_size; i++) {
            printf("%d ", merged[i]);
        }
        printf("\n");
        free(merged);
    }

    free_list(head);
    return 0;
}