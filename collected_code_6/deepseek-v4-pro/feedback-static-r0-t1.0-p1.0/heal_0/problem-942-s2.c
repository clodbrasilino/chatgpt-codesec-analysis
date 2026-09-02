#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    size_t size;
} List;

List* list_create(void) {
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

void list_destroy(List* list) {
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

bool list_push_back(List* list, int value) {
    if (list == NULL) {
        return false;
    }
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return false;
    }
    new_node->data = value;
    new_node->next = NULL;
    
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->size++;
    return true;
}

bool list_contains_any(const List* list, const int* values, size_t count) {
    if (list == NULL || values == NULL || count == 0) {
        return false;
    }
    
    for (size_t i = 0; i < count; i++) {
        Node* current = list->head;
        while (current != NULL) {
            if (current->data == values[i]) {
                return true;
            }
            current = current->next;
        }
    }
    
    return false;
}

int main(void) {
    List* list = list_create();
    if (list == NULL) {
        fprintf(stderr, "Failed to allocate memory for list\n");
        return EXIT_FAILURE;
    }
    
    if (!list_push_back(list, 10) ||
        !list_push_back(list, 20) ||
        !list_push_back(list, 30) ||
        !list_push_back(list, 40)) {
        fprintf(stderr, "Failed to add elements to list\n");
        list_destroy(list);
        return EXIT_FAILURE;
    }
    
    int search_values[] = {15, 25, 20};
    size_t search_count = sizeof(search_values) / sizeof(search_values[0]);
    
    if (list_contains_any(list, search_values, search_count)) {
        printf("At least one element is present in the list\n");
    } else {
        printf("No matching elements found\n");
    }
    
    list_destroy(list);
    return EXIT_SUCCESS;
}