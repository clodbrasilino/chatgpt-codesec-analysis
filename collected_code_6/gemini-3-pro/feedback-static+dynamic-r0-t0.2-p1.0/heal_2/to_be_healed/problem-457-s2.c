#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    size_t length;
} List;

List* find_min_length_sublist(List** lists, size_t num_lists) {
    if (lists == NULL || num_lists == 0) {
        return NULL;
    }

    List* min_list = NULL;
    size_t min_length = SIZE_MAX;

    for (size_t i = 0; i < num_lists; ++i) {
        if (lists[i] != NULL && lists[i]->length < min_length) {
            min_length = lists[i]->length;
            min_list = lists[i];
        }
    }

    return min_list;
}

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

List* create_list(const int* arr, size_t size) {
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) {
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->length = size;

    if (size == 0) {
        return list;
    }

    list->head = create_node(arr[0]);
    Node* current = list->head;
    for (size_t i = 1; i < size; ++i) {
        current->next = create_node(arr[i]);
        current = current->next;
    }

    return list;
}

void free_list(List* list) {
    if (list == NULL) {
        return;
    }
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

int main(void) {
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
    int arr3[] = {6, 7, 8, 9};

    List* list1 = create_list(arr1, 3);
    List* list2 = create_list(arr2, 2);
    List* list3 = create_list(arr3, 4);

    List* lists[] = {list1, list2, list3};
    size_t num_lists = sizeof(lists) / sizeof(lists[0]);

    List* min_list = find_min_length_sublist(lists, num_lists);

    if (min_list != NULL) {
        printf("Minimum length: %zu\n", min_list->length);
        printf("Elements: ");
        Node* current = min_list->head;
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }

    free_list(list1);
    free_list(list2);
    free_list(list3);

    return 0;
}