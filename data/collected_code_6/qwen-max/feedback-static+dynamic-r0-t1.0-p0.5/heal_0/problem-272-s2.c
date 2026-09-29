#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct Node {
    Tuple data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    size_t size;
} List;

List* create_list() {
    List *list = (List*)malloc(sizeof(List));
    if (list == NULL) exit(EXIT_FAILURE);
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void add_tuple(List *list, int first, int second) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) exit(EXIT_FAILURE);
    new_node->data.first = first;
    new_node->data.second = second;
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

int extract_rear_element(List *list) {
    if (list->size == 0) return -1; // Assuming -1 as an error value

    Node *current = list->head;
    Node *prev = NULL;

    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    int rear_element = current->data.second;

    if (prev == NULL) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        prev->next = NULL;
        list->tail = prev;
    }

    free(current);
    list->size--;

    return rear_element;
}

void free_list(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

int main() {
    List *list = create_list();
    add_tuple(list, 1, 2);
    add_tuple(list, 3, 4);
    add_tuple(list, 5, 6);

    int rear_element = extract_rear_element(list);
    printf("Rear element: %d\n", rear_element);

    free_list(list);
    return 0;
}