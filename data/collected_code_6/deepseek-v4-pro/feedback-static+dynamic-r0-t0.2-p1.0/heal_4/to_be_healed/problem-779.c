#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Node {
    int *data;
    int size;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int count;
} ListOfLists;

Node *create_node(const int *data, int size) {
    Node *node;
    size_t alloc_size;
    
    if (size <= 0) {
        return NULL;
    }
    
    if ((size_t)size > SIZE_MAX / sizeof(int)) {
        return NULL;
    }
    
    node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    
    alloc_size = (size_t)size * sizeof(int);
    
    node->data = (int *)malloc(alloc_size);
    if (node->data == NULL) {
        free(node);
        return NULL;
    }
    
    if (data != NULL) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(node->data, data, alloc_size);
    } else {
        memset(node->data, 0, alloc_size);
    }
    
    node->size = size;
    node->next = NULL;
    return node;
}

void free_list_of_lists(ListOfLists *list) {
    Node *current;
    Node *next;
    
    if (list == NULL) {
        return;
    }
    
    current = list->head;
    while (current != NULL) {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    list->head = NULL;
    list->count = 0;
}

int lists_equal(const Node *a, const Node *b) {
    int i;
    
    if (a == NULL || b == NULL) {
        return 0;
    }
    if (a->size != b->size) {
        return 0;
    }
    for (i = 0; i < a->size; i++) {
        if (a->data[i] != b->data[i]) {
            return 0;
        }
    }
    return 1;
}

int count_unique_lists(ListOfLists *list) {
    int unique_count;
    Node *current;
    Node *check;
    /* Possible weaknesses found:
     *  The scope of the variable 'is_unique' can be reduced. [variableScope]
     */
    int is_unique;
    
    if (list == NULL || list->head == NULL) {
        return 0;
    }
    
    unique_count = 0;
    current = list->head;
    
    while (current != NULL) {
        is_unique = 1;
        check = list->head;
        
        while (check != current) {
            if (lists_equal(check, current)) {
                is_unique = 0;
                break;
            }
            check = check->next;
        }
        
        if (is_unique) {
            unique_count++;
        }
        current = current->next;
    }
    
    return unique_count;
}

int main(void) {
    ListOfLists list;
    /* Possible weaknesses found:
     *  Variable 'arr1' can be declared as const array [constVariable]
     */
    int arr1[] = {1, 2, 3};
    /* Possible weaknesses found:
     *  Variable 'arr2' can be declared as const array [constVariable]
     */
    int arr2[] = {4, 5, 6};
    /* Possible weaknesses found:
     *  Variable 'arr3' can be declared as const array [constVariable]
     */
    int arr3[] = {1, 2, 3};
    /* Possible weaknesses found:
     *  Variable 'arr4' can be declared as const array [constVariable]
     */
    int arr4[] = {7, 8};
    /* Possible weaknesses found:
     *  Variable 'arr5' can be declared as const array [constVariable]
     */
    int arr5[] = {4, 5, 6};
    Node *node1;
    Node *node2;
    Node *node3;
    Node *node4;
    Node *node5;
    int result;
    
    list.head = NULL;
    list.count = 0;
    
    node1 = create_node(arr1, 3);
    node2 = create_node(arr2, 3);
    node3 = create_node(arr3, 3);
    node4 = create_node(arr4, 2);
    node5 = create_node(arr5, 3);
    
    if (node1 == NULL || node2 == NULL || node3 == NULL || node4 == NULL || node5 == NULL) {
        free(node1);
        free(node2);
        free(node3);
        free(node4);
        free(node5);
        return 1;
    }
    
    list.head = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    list.count = 5;
    
    result = count_unique_lists(&list);
    printf("%d\n", result);
    
    free_list_of_lists(&list);
    
    return 0;
}