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
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

bool list_append(List* list, int value) {
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

bool list_contains(const List* list, int value) {
    if (list == NULL) {
        return false;
    }
    Node* current = list->head;
    while (current != NULL) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

List* list_difference(const List* list1, const List* list2) {
    if (list1 == NULL || list2 == NULL) {
        return NULL;
    }
    
    List* result = list_create();
    if (result == NULL) {
        return NULL;
    }
    
    Node* current = list1->head;
    while (current != NULL) {
        if (!list_contains(list2, current->data)) {
            if (!list_append(result, current->data)) {
                list_destroy(result);
                return NULL;
            }
        }
        current = current->next;
    }
    
    return result;
}

void list_print(const List* list) {
    if (list == NULL) {
        printf("[]\n");
        return;
    }
    
    printf("[");
    Node* current = list->head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

int main(void) {
    List* list1 = list_create();
    List* list2 = list_create();
    
    if (list1 == NULL || list2 == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        list_destroy(list1);
        list_destroy(list2);
        return EXIT_FAILURE;
    }
    
    int values1[] = {1, 2, 3, 4, 5};
    int values2[] = {2, 4, 6};
    
    for (size_t i = 0; i < sizeof(values1) / sizeof(values1[0]); i++) {
        if (!list_append(list1, values1[i])) {
            fprintf(stderr, "Failed to append to list1\n");
            list_destroy(list1);
            list_destroy(list2);
            return EXIT_FAILURE;
        }
    }
    
    for (size_t i = 0; i < sizeof(values2) / sizeof(values2[0]); i++) {
        if (!list_append(list2, values2[i])) {
            fprintf(stderr, "Failed to append to list2\n");
            list_destroy(list1);
            list_destroy(list2);
            return EXIT_FAILURE;
        }
    }
    
    printf("List 1: ");
    list_print(list1);
    printf("List 2: ");
    list_print(list2);
    
    List* difference = list_difference(list1, list2);
    if (difference == NULL) {
        fprintf(stderr, "Failed to compute difference\n");
        list_destroy(list1);
        list_destroy(list2);
        return EXIT_FAILURE;
    }
    
    printf("Difference (list1 - list2): ");
    list_print(difference);
    
    list_destroy(difference);
    list_destroy(list1);
    list_destroy(list2);
    
    return EXIT_SUCCESS;
}