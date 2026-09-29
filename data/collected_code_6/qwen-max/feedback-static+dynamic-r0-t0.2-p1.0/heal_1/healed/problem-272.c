#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct Node {
    Tuple data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    size_t size;
} List;

List* create_list() {
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) exit(EXIT_FAILURE);
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void add_tuple(List* list, Tuple tuple) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) exit(EXIT_FAILURE);
    new_node->data = tuple;
    new_node->next = NULL;
    if (list->tail != NULL) {
        list->tail->next = new_node;
    }
    list->tail = new_node;
    if (list->head == NULL) {
        list->head = new_node;
    }
    list->size++;
}

int extract_rear(List* list) {
    if (list->size == 0) return -1; 
    Node* current = list->head;
    Node* prev = NULL;
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }
    int rear_value = current->data.second;
    if (prev != NULL) {
        prev->next = NULL;
    } else {
        list->head = NULL;
    }
    list->tail = prev;
    free(current);
    list->size--;
    return rear_value;
}

void free_list(List* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

int main() {
    List* list = create_list();
    add_tuple(list, (Tuple){1, 2});
    add_tuple(list, (Tuple){3, 4});
    add_tuple(list, (Tuple){5, 6});

    int rear_value = extract_rear(list);
    printf("Rear value: %d\n", rear_value);

    free_list(list);
    return 0;
}