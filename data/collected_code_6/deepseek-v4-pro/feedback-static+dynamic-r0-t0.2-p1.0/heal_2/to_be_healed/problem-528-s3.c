#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    int length;
} List;

List** find_min_length_lists(List** lists, int num_lists, int* result_count) {
    if (lists == NULL || num_lists <= 0 || result_count == NULL) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    for (int i = 0; i < num_lists; i++) {
        if (lists[i] == NULL) {
            *result_count = 0;
            return NULL;
        }
    }

    int min_length = lists[0]->length;
    for (int i = 1; i < num_lists; i++) {
        if (lists[i]->length < min_length) {
            min_length = lists[i]->length;
        }
    }

    int count = 0;
    for (int i = 0; i < num_lists; i++) {
        if (lists[i]->length == min_length) {
            count++;
        }
    }

    List** result = (List**)malloc(count * sizeof(List*));
    if (result == NULL) {
        *result_count = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < num_lists; i++) {
        if (lists[i]->length == min_length) {
            result[index++] = lists[i];
        }
    }

    *result_count = count;
    return result;
}

List* create_list(const int* arr, int size) {
    if (arr == NULL || size < 0) {
        return NULL;
    }

    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->length = 0;

    Node* current = NULL;
    for (int i = 0; i < size; i++) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        if (new_node == NULL) {
            Node* temp = list->head;
            while (temp != NULL) {
                Node* next = temp->next;
                free(temp);
                temp = next;
            }
            free(list);
            return NULL;
        }
        new_node->data = arr[i];
        new_node->next = NULL;
        
        if (list->head == NULL) {
            list->head = new_node;
        } else {
            current->next = new_node;
        }
        current = new_node;
        list->length++;
    }
    return list;
}

void free_list(List* list) {
    if (list == NULL) return;
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

int main() {
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
    int arr3[] = {6};
    /* Possible weaknesses found:
     *  Variable 'arr4' can be declared as const array [constVariable]
     */
    int arr4[] = {7, 8, 9, 10};

    List* list1 = create_list(arr1, 3);
    List* list2 = create_list(arr2, 2);
    List* list3 = create_list(arr3, 1);
    List* list4 = create_list(arr4, 4);

    if (list1 == NULL || list2 == NULL || list3 == NULL || list4 == NULL) {
        free_list(list1);
        free_list(list2);
        free_list(list3);
        free_list(list4);
        return 1;
    }

    List* lists[] = {list1, list2, list3, list4};
    int result_count = 0;

    List** min_lists = find_min_length_lists(lists, 4, &result_count);

    if (min_lists != NULL) {
        printf("Minimum length lists: %d\n", result_count);
        for (int i = 0; i < result_count; i++) {
            printf("List %d (length %d): ", i + 1, min_lists[i]->length);
            Node* current = min_lists[i]->head;
            while (current != NULL) {
                printf("%d ", current->data);
                current = current->next;
            }
            printf("\n");
        }
        free(min_lists);
    }

    free_list(list1);
    free_list(list2);
    free_list(list3);
    free_list(list4);

    return 0;
}