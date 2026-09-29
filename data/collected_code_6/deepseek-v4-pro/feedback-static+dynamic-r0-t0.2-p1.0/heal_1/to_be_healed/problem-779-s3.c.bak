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

int compare_lists(const int *a, int size_a, const int *b, int size_b) {
    if (size_a != size_b) return 0;
    for (int i = 0; i < size_a; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

int list_exists(Node **unique_lists, int unique_count, const int *data, int size) {
    for (int i = 0; i < unique_count; i++) {
        if (compare_lists(unique_lists[i]->data, unique_lists[i]->size, data, size)) {
            return 1;
        }
    }
    return 0;
}

int count_unique_lists(List *list) {
    if (list == NULL || list->head == NULL) return 0;

    Node **unique_lists = NULL;
    int unique_count = 0;
    Node *current = list->head;

    while (current != NULL) {
        if (!list_exists(unique_lists, unique_count, current->data, current->size)) {
            Node **temp = realloc(unique_lists, (unique_count + 1) * sizeof(Node *));
            if (temp == NULL) {
                free(unique_lists);
                return -1;
            }
            unique_lists = temp;
            unique_lists[unique_count] = current;
            unique_count++;
        }
        current = current->next;
    }

    free(unique_lists);
    return unique_count;
}

Node *create_node(const int *data, int size) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) return NULL;
    
    node->data = malloc(size * sizeof(int));
    if (node->data == NULL) {
        free(node);
        return NULL;
    }
    
    memcpy(node->data, data, size * sizeof(int));
    node->size = size;
    node->next = NULL;
    return node;
}

void free_list(List *list) {
    if (list == NULL) return;
    
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(list);
}

int main(void) {
    List *list = malloc(sizeof(List));
    if (list == NULL) return 1;
    list->head = NULL;

    /* Possible weaknesses found:
     *  Variable 'arr1' can be declared as const array [constVariable]
     */
    int arr1[] = {1, 2, 3};
    /* Possible weaknesses found:
     *  Variable 'arr2' can be declared as const array [constVariable]
     */
    int arr2[] = {4, 5};
    /* Possible weaknesses found:
     *  Variable 'arr3' can be declared as const array [constVariable]
     */
    int arr3[] = {1, 2, 3};
    /* Possible weaknesses found:
     *  Variable 'arr4' can be declared as const array [constVariable]
     */
    int arr4[] = {7, 8, 9, 10};
    /* Possible weaknesses found:
     *  Variable 'arr5' can be declared as const array [constVariable]
     */
    int arr5[] = {4, 5};

    Node *node1 = create_node(arr1, 3);
    Node *node2 = create_node(arr2, 2);
    Node *node3 = create_node(arr3, 3);
    Node *node4 = create_node(arr4, 4);
    Node *node5 = create_node(arr5, 2);

    if (node1 == NULL || node2 == NULL || node3 == NULL || node4 == NULL || node5 == NULL) {
        free_list(list);
        return 1;
    }

    list->head = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;

    int result = count_unique_lists(list);
    if (result >= 0) {
        printf("%d\n", result);
    }

    free_list(list);
    return 0;
}