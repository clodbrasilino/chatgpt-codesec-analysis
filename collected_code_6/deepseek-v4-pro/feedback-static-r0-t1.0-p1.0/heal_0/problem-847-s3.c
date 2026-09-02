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

void list_destroy(List *list) {
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

List *list_copy_from_singleton(List *source) {
    if (source == NULL || source->size != 1 || source->head == NULL) {
        return NULL;
    }
    
    List *copy = list_create();
    if (copy == NULL) {
        return NULL;
    }
    
    if (list_append(copy, source->head->data) != 0) {
        list_destroy(copy);
        return NULL;
    }
    
    return copy;
}

void list_print(const List *list) {
    if (list == NULL) {
        printf("NULL\n");
        return;
    }
    Node *current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    List *source = list_create();
    if (source == NULL) {
        return 1;
    }
    
    if (list_append(source, 42) != 0) {
        list_destroy(source);
        return 1;
    }
    
    List *copy = list_copy_from_singleton(source);
    if (copy == NULL) {
        list_destroy(source);
        return 1;
    }
    
    printf("Source: ");
    list_print(source);
    printf("Copy: ");
    list_print(copy);
    
    list_destroy(source);
    list_destroy(copy);
    
    return 0;
}