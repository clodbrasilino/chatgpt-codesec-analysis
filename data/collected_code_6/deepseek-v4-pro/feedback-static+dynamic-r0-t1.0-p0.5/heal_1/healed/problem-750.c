#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int first;
    int second;
} Tuple;

typedef struct Node {
    Tuple data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    Node *tail;
    size_t size;
} List;

List *list_create(void) {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

int list_add_tuple(List *list, Tuple tuple) {
    Node *new_node;
    
    if (list == NULL) {
        return -1;
    }
    
    new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return -1;
    }
    
    new_node->data = tuple;
    new_node->next = NULL;
    
    if (list->tail == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    
    list->size++;
    return 0;
}

void list_destroy(List *list) {
    Node *current;
    Node *next;
    
    if (list == NULL) {
        return;
    }
    
    current = list->head;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    free(list);
}

int main(void) {
    List *list;
    Tuple t1 = {10, 20};
    Tuple t2 = {30, 40};
    Tuple t3 = {50, 60};
    
    list = list_create();
    if (list == NULL) {
        fprintf(stderr, "Failed to create list\n");
        return 1;
    }
    
    if (list_add_tuple(list, t1) != 0) {
        fprintf(stderr, "Failed to add tuple\n");
        list_destroy(list);
        return 1;
    }
    
    if (list_add_tuple(list, t2) != 0) {
        fprintf(stderr, "Failed to add tuple\n");
        list_destroy(list);
        return 1;
    }
    
    if (list_add_tuple(list, t3) != 0) {
        fprintf(stderr, "Failed to add tuple\n");
        list_destroy(list);
        return 1;
    }
    
    printf("List size: %zu\n", list->size);
    printf("First tuple: %d, %d\n", list->head->data.first, list->head->data.second);
    printf("Second tuple: %d, %d\n", list->head->next->data.first, list->head->next->data.second);
    printf("Third tuple: %d, %d\n", list->head->next->next->data.first, list->head->next->next->data.second);
    
    list_destroy(list);
    return 0;
}