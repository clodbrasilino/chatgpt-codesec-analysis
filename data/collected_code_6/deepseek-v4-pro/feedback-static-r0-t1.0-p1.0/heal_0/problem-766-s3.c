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
    if (!list) return NULL;
    list->head = NULL;
    list->size = 0;
    return list;
}

int list_append(List *list, int value) {
    if (!list) return -1;
    
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) return -1;
    
    new_node->data = value;
    new_node->next = NULL;
    
    if (!list->head) {
        list->head = new_node;
    } else {
        Node *current = list->head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }
    
    list->size++;
    return 0;
}

void list_destroy(List *list) {
    if (!list) return;
    
    Node *current = list->head;
    while (current) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    
    free(list);
}

void iterate_consecutive_pairs(const List *list, void (*callback)(int, int)) {
    if (!list || !callback || list->size < 2) return;
    
    Node *current = list->head;
    Node *next = current->next;
    
    while (current && next) {
        callback(current->data, next->data);
        current = next;
        next = next->next;
    }
}

void print_pair(int a, int b) {
    printf("(%d, %d)\n", a, b);
}

int main(void) {
    List *list = list_create();
    if (!list) return 1;
    
    int values[] = {10, 20, 30, 40, 50};
    size_t count = sizeof(values) / sizeof(values[0]);
    
    for (size_t i = 0; i < count; i++) {
        if (list_append(list, values[i]) != 0) {
            list_destroy(list);
            return 1;
        }
    }
    
    iterate_consecutive_pairs(list, print_pair);
    
    list_destroy(list);
    return 0;
}