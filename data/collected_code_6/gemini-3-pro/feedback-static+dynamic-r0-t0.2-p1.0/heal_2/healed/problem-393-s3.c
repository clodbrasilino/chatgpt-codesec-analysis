#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    size_t length;
} List;

const List* find_max_length_list(const List* const* lists, size_t num_lists) {
    if (lists == NULL || num_lists == 0) {
        return NULL;
    }

    const List* max_list = lists[0];
    for (size_t i = 1; i < num_lists; ++i) {
        if (lists[i] != NULL && (max_list == NULL || lists[i]->length > max_list->length)) {
            max_list = lists[i];
        }
    }

    return max_list;
}

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

List* create_list(const int* arr, size_t size) {
    List* new_list = (List*)malloc(sizeof(List));
    if (new_list == NULL) {
        return NULL;
    }
    new_list->head = NULL;
    new_list->length = 0;

    if (size == 0 || arr == NULL) {
        return new_list;
    }

    new_list->head = create_node(arr[0]);
    if (new_list->head == NULL) {
        free(new_list);
        return NULL;
    }
    new_list->length = 1;

    Node* current = new_list->head;
    for (size_t i = 1; i < size; ++i) {
        current->next = create_node(arr[i]);
        if (current->next == NULL) {
            Node* temp = new_list->head;
            while (temp != NULL) {
                Node* next = temp->next;
                free(temp);
                temp = next;
            }
            free(new_list);
            return NULL;
        }
        current = current->next;
        new_list->length++;
    }

    return new_list;
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
    const int arr1[] = {1, 2, 3};
    const int arr2[] = {4, 5, 6, 7, 8};
    const int arr3[] = {9};

    List* list1 = create_list(arr1, 3);
    List* list2 = create_list(arr2, 5);
    List* list3 = create_list(arr3, 1);

    if (list1 == NULL || list2 == NULL || list3 == NULL) {
        free_list(list1);
        free_list(list2);
        free_list(list3);
        return 1;
    }

    const List* lists[] = {list1, list2, list3};
    size_t num_lists = sizeof(lists) / sizeof(lists[0]);

    const List* max_list = find_max_length_list(lists, num_lists);

    if (max_list != NULL) {
        printf("Max list length: %zu\n", max_list->length);
    }

    free_list(list1);
    free_list(list2);
    free_list(list3);

    return 0;
}