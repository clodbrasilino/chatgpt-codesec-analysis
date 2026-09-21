#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Node {
    int *data;
    int size;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

Node *create_node(const int *data, int size) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) return NULL;
    node->data = NULL;
    node->size = 0;
    node->next = NULL;
    if (size > 0 && data != NULL) {
        if (size > SIZE_MAX / sizeof(int)) {
            free(node);
            return NULL;
        }
        size_t alloc_size = (size_t)size * sizeof(int);
        node->data = (int *)malloc(alloc_size);
        if (!node->data) {
            free(node);
            return NULL;
        }
        memcpy(node->data, data, alloc_size);
        node->size = size;
    }
    return node;
}

void free_list(List *list) {
    if (!list) return;
    Node *current = list->head;
    while (current) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(list);
}

int compare_lists(const int *a, int size_a, const int *b, int size_b) {
    if (size_a != size_b) return 0;
    for (int i = 0; i < size_a; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

int is_unique(const Node *head, const Node *target) {
    if (!target) return 0;
    const Node *current = head;
    while (current && current != target) {
        if (compare_lists(current->data, current->size, target->data, target->size)) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}

int count_unique_lists(const List *list) {
    if (!list || !list->head) return 0;
    int count = 0;
    const Node *current = list->head;
    while (current) {
        if (is_unique(list->head, current)) {
            count++;
        }
        current = current->next;
    }
    return count;
}

int main(void) {
    List *list = (List *)malloc(sizeof(List));
    if (!list) return 1;
    list->head = NULL;

    const int arr1[] = {1, 2, 3};
    const int arr2[] = {4, 5};
    const int arr3[] = {1, 2, 3};
    const int arr4[] = {7, 8, 9, 10};
    const int arr5[] = {4, 5};

    Node *n1 = create_node(arr1, 3);
    Node *n2 = create_node(arr2, 2);
    Node *n3 = create_node(arr3, 3);
    Node *n4 = create_node(arr4, 4);
    Node *n5 = create_node(arr5, 2);

    if (!n1 || !n2 || !n3 || !n4 || !n5) {
        if (n1) { free(n1->data); free(n1); }
        if (n2) { free(n2->data); free(n2); }
        if (n3) { free(n3->data); free(n3); }
        if (n4) { free(n4->data); free(n4); }
        if (n5) { free(n5->data); free(n5); }
        free(list);
        return 1;
    }

    list->head = n1;
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;

    int unique_count = count_unique_lists(list);
    printf("%d\n", unique_count);

    free_list(list);
    return 0;
}