#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

typedef struct Node {
    int *data;
    int size;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

static int safe_mul_check(int a, int b) {
    if (a < 0 || b < 0) return -1;
    if (a == 0 || b == 0) return 0;
    if (a > INT_MAX / b) return -1;
    return a * b;
}

Node *create_node(const int *data, int size) {
    Node *node;

    if (size < 0) {
        return NULL;
    }

    node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = NULL;
    node->size = 0;
    node->next = NULL;

    if (size > 0) {
        int alloc_size = safe_mul_check(sizeof(int), size);
        if (alloc_size < 0) {
            free(node);
            return NULL;
        }
        node->data = (int *)malloc((size_t)alloc_size);
        if (node->data == NULL) {
            free(node);
            return NULL;
        }
        node->size = size;
        if (data != NULL) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(node->data, data, (size_t)alloc_size);
        }
    }
    return node;
}

void free_list(List *list) {
    if (list == NULL) {
        return;
    }
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(list);
}

int compare_lists(const int *a, int size_a, const int *b, int size_b) {
    size_t i;

    if (size_a != size_b) {
        return 0;
    }
    if (a == NULL || b == NULL) {
        if (a == NULL && b == NULL) {
            return 1;
        }
        return 0;
    }
    for (i = 0; i < (size_t)size_a; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

int count_unique_lists(List *list) {
    if (list == NULL || list->head == NULL) {
        return 0;
    }

    int count = 0;
    Node *current = list->head;

    while (current != NULL) {
        int is_unique = 1;
        Node *check = list->head;

        while (check != current) {
            if (compare_lists(current->data, current->size, check->data, check->size)) {
                is_unique = 0;
                break;
            }
            check = check->next;
        }

        if (is_unique) {
            count++;
        }
        current = current->next;
    }

    return count;
}

int main(void) {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return 1;
    }
    list->head = NULL;

    const int arr1[] = {1, 2, 3};
    const int arr2[] = {4, 5, 6};
    const int arr3[] = {1, 2, 3};
    const int arr4[] = {7, 8};
    const int arr5[] = {4, 5, 6};

    Node *node1 = create_node(arr1, 3);
    Node *node2 = create_node(arr2, 3);
    Node *node3 = create_node(arr3, 3);
    Node *node4 = create_node(arr4, 2);
    Node *node5 = create_node(arr5, 3);

    if (node1 == NULL || node2 == NULL || node3 == NULL || node4 == NULL || node5 == NULL) {
        free(node1 ? node1->data : NULL);
        free(node1);
        free(node2 ? node2->data : NULL);
        free(node2);
        free(node3 ? node3->data : NULL);
        free(node3);
        free(node4 ? node4->data : NULL);
        free(node4);
        free(node5 ? node5->data : NULL);
        free(node5);
        free(list);
        return 1;
    }

    list->head = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;

    int unique_count = count_unique_lists(list);
    printf("%d\n", unique_count);

    free_list(list);

    return 0;
}