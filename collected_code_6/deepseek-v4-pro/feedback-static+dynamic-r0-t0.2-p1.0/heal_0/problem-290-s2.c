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

int list_length(List* list) {
    if (list == NULL) return 0;
    return list->length;
}

List** find_max_length_lists(List** lists, int num_lists, int* result_count) {
    if (lists == NULL || num_lists <= 0 || result_count == NULL) {
        *result_count = 0;
        return NULL;
    }

    int max_len = 0;
    int count = 0;
    int i;

    for (i = 0; i < num_lists; i++) {
        int len = list_length(lists[i]);
        if (len > max_len) {
            max_len = len;
            count = 1;
        } else if (len == max_len) {
            count++;
        }
    }

    List** result = (List**)malloc(count * sizeof(List*));
    if (result == NULL) {
        *result_count = 0;
        return NULL;
    }

    int index = 0;
    for (i = 0; i < num_lists; i++) {
        if (list_length(lists[i]) == max_len) {
            result[index++] = lists[i];
        }
    }

    *result_count = count;
    return result;
}

Node* create_node(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) return NULL;
    node->data = data;
    node->next = NULL;
    return node;
}

List* create_list(int* arr, int size) {
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) return NULL;
    list->head = NULL;
    list->length = 0;

    if (size == 0) return list;

    Node* current = NULL;
    for (int i = 0; i < size; i++) {
        Node* node = create_node(arr[i]);
        if (node == NULL) {
            Node* temp = list->head;
            while (temp != NULL) {
                Node* next = temp->next;
                free(temp);
                temp = next;
            }
            free(list);
            return NULL;
        }
        if (list->head == NULL) {
            list->head = node;
            current = node;
        } else {
            current->next = node;
            current = node;
        }
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
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6, 7};
    int arr3[] = {8, 9};
    int arr4[] = {10, 11, 12, 13};

    List* list1 = create_list(arr1, 3);
    List* list2 = create_list(arr2, 4);
    List* list3 = create_list(arr3, 2);
    List* list4 = create_list(arr4, 4);

    List* lists[] = {list1, list2, list3, list4};
    int result_count = 0;

    List** result = find_max_length_lists(lists, 4, &result_count);

    printf("Maximum length: %d\n", list_length(result[0]));
    printf("Number of lists with max length: %d\n", result_count);
    for (int i = 0; i < result_count; i++) {
        printf("List %d: ", i + 1);
        Node* current = result[i]->head;
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }

    free(result);
    free_list(list1);
    free_list(list2);
    free_list(list3);
    free_list(list4);

    return 0;
}