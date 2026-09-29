#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    size_t size;
} List;

List *list_create(void) {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

int list_append(List *list, int data) {
    if (list == NULL) {
        return -1;
    }
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return -1;
    }
    new_node->data = data;
    new_node->next = NULL;
    
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->size++;
    return 0;
}

void list_free(List *list) {
    if (list == NULL) {
        return;
    }
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void iterate_pairs(List *list) {
    if (list == NULL || list->head == NULL || list->head->next == NULL) {
        return;
    }
    
    Node *current = list->head;
    while (current != NULL && current->next != NULL) {
        printf("(%d, %d)\n", current->data, current->next->data);
        current = current->next;
    }
}

int main(void) {
    List *list = list_create();
    if (list == NULL) {
        fprintf(stderr, "Failed to create list\n");
        return 1;
    }
    
    int values[] = {1, 2, 3, 4, 5};
    size_t num_values = sizeof(values) / sizeof(values[0]);
    
    for (size_t i = 0; i < num_values; i++) {
        if (list_append(list, values[i]) != 0) {
            fprintf(stderr, "Failed to append value %d\n", values[i]);
            list_free(list);
            return 1;
        }
    }
    
    printf("Consecutive pairs:\n");
    iterate_pairs(list);
    
    list_free(list);
    return 0;
}