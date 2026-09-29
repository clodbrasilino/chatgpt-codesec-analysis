#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct ListArray {
    Node** lists;
    size_t count;
} ListArray;

Node* create_node(int data);
void free_list(Node* head);
void free_list_array(ListArray* array);
ListArray split_list(Node* head, size_t n);

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node != NULL) {
        new_node->data = data;
        new_node->next = NULL;
    }
    return new_node;
}

void free_list(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

void free_list_array(ListArray* array) {
    if (array != NULL) {
        if (array->lists != NULL) {
            for (size_t i = 0; i < array->count; i++) {
                free_list(array->lists[i]);
            }
            free(array->lists);
            array->lists = NULL;
        }
        array->count = 0;
    }
}

ListArray split_list(Node* head, size_t n) {
    ListArray result = {NULL, 0};

    if (n == 0 || head == NULL) {
        return result;
    }

    size_t length = 0;
    Node* current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }

    result.count = (length + n - 1) / n;
    result.lists = (Node**)malloc(result.count * sizeof(Node*));

    if (result.lists == NULL) {
        result.count = 0;
        return result;
    }

    current = head;
    for (size_t i = 0; i < result.count; i++) {
        result.lists[i] = current;
        Node* prev = NULL;
        for (size_t j = 0; j < n && current != NULL; j++) {
            prev = current;
            current = current->next;
        }
        if (prev != NULL) {
            prev->next = NULL;
        }
    }

    return result;
}

int main(void) {
    Node* head = create_node(1);
    if (head == NULL) {
        return EXIT_FAILURE;
    }

    Node* current = head;
    for (int i = 2; i <= 10; i++) {
        Node* next_node = create_node(i);
        if (next_node == NULL) {
            free_list(head);
            return EXIT_FAILURE;
        }
        current->next = next_node;
        current = current->next;
    }

    size_t split_size = 3;
    ListArray split_result = split_list(head, split_size);

    if (split_result.lists == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < split_result.count; i++) {
        Node* chunk_current = split_result.lists[i];
        while (chunk_current != NULL) {
            printf("%d ", chunk_current->data);
            chunk_current = chunk_current->next;
        }
        printf("\n");
    }

    free_list_array(&split_result);

    return EXIT_SUCCESS;
}