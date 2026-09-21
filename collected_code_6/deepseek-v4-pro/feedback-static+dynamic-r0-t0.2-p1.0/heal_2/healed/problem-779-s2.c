#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    if (size > 0) {
        node->data = (int *)malloc(sizeof(int) * size);
        if (!node->data) {
            free(node);
            return NULL;
        }
        if (data) {
            memcpy(node->data, data, sizeof(int) * size);
        } else {
            memset(node->data, 0, sizeof(int) * size);
        }
    } else {
        node->data = NULL;
    }
    node->size = size;
    node->next = NULL;
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

int lists_equal(const Node *a, const Node *b) {
    if (!a || !b) return 0;
    if (a->size != b->size) return 0;
    for (int i = 0; i < a->size; i++) {
        if (a->data[i] != b->data[i]) return 0;
    }
    return 1;
}

int count_unique_lists(List *list) {
    if (!list || !list->head) return 0;
    
    int count = 0;
    Node *current = list->head;
    
    while (current) {
        int is_unique = 1;
        Node *check = list->head;
        while (check != current) {
            if (lists_equal(check, current)) {
                is_unique = 0;
                break;
            }
            check = check->next;
        }
        if (is_unique) count++;
        current = current->next;
    }
    
    return count;
}

int main(void) {
    List *list = (List *)malloc(sizeof(List));
    if (!list) return 1;
    list->head = NULL;
    
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};
    int arr3[] = {1, 2, 3};
    int arr4[] = {7, 8};
    int arr5[] = {4, 5, 6};
    
    Node *n1 = create_node(arr1, 3);
    Node *n2 = create_node(arr2, 3);
    Node *n3 = create_node(arr3, 3);
    Node *n4 = create_node(arr4, 2);
    Node *n5 = create_node(arr5, 3);
    
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