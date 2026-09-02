#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Tuple;

typedef struct Node {
    Tuple data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    int size;
} List;

List* create_list() {
    List *list = (List*)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void add_tuple(List *list, int key, int value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data.key = key;
    new_node->data.value = value;
    new_node->next = NULL;
    
    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;
}

Tuple* extract_rear(List *list) {
    if (list->size == 0) {
        return NULL;
    }

    Node *current = list->head;
    Node *prev = NULL;

    while (current != list->tail) {
        prev = current;
        current = current->next;
    }

    if (prev != NULL) {
        prev->next = NULL;
    } else {
        list->head = NULL;
    }
    list->tail = prev;
    list->size--;

    Tuple *tuple = (Tuple*)malloc(sizeof(Tuple));
    tuple->key = current->data.key;
    tuple->value = current->data.value;
    free(current);
    return tuple;
}

int main() {
    List *list = create_list();
    add_tuple(list, 1, 10);
    add_tuple(list, 2, 20);
    add_tuple(list, 3, 30);

    Tuple *rear = extract_rear(list);
    if (rear != NULL) {
        printf("Extracted: Key = %d, Value = %d\n", rear->key, rear->value);
        free(rear);
    }

    rear = extract_rear(list);
    if (rear != NULL) {
        printf("Extracted: Key = %d, Value = %d\n", rear->key, rear->value);
        free(rear);
    }

    rear = extract_rear(list);
    if (rear != NULL) {
        printf("Extracted: Key = %d, Value = %d\n", rear->key, rear->value);
        free(rear);
    }

    rear = extract_rear(list);
    if (rear == NULL) {
        printf("List is empty.\n");
    }

    free(list);
    return 0;
}