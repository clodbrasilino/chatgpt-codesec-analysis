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

Node *create_node(int *data, int size) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = (int *)malloc(sizeof(int) * size);
    if (node->data == NULL) {
        free(node);
        return NULL;
    }
    memcpy(node->data, data, sizeof(int) * size);
    node->size = size;
    node->next = NULL;
    return node;
}

void free_list(List *list) {
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
    if (size_a != size_b) {
        return 0;
    }
    for (int i = 0; i < size_a; i++) {
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
    
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};
    int arr3[] = {1, 2, 3};
    int arr4[] = {7, 8};
    int arr5[] = {4, 5, 6};
    
    Node *node1 = create_node(arr1, 3);
    Node *node2 = create_node(arr2, 3);
    Node *node3 = create_node(arr3, 3);
    Node *node4 = create_node(arr4, 2);
    Node *node5 = create_node(arr5, 3);
    
    if (node1 == NULL || node2 == NULL || node3 == NULL || node4 == NULL || node5 == NULL) {
        if (node1 != NULL) free(node1->data);
        if (node1 != NULL) free(node1);
        if (node2 != NULL) free(node2->data);
        if (node2 != NULL) free(node2);
        if (node3 != NULL) free(node3->data);
        if (node3 != NULL) free(node3);
        if (node4 != NULL) free(node4->data);
        if (node4 != NULL) free(node4);
        if (node5 != NULL) free(node5->data);
        if (node5 != NULL) free(node5);
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