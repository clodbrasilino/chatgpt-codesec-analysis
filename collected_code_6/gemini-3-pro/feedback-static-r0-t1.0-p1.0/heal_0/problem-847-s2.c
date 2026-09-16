#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Tuple {
    Node* list;
} Tuple;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Node* copy_list_from_tuple(const Tuple* tuple) {
    if (!tuple || !tuple->list) {
        return NULL;
    }

    Node* copied_list = NULL;
    Node* tail = NULL;
    Node* current = tuple->list;

    while (current) {
        Node* new_node = create_node(current->data);
        if (!copied_list) {
            copied_list = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
        current = current->next;
    }

    return copied_list;
}

void free_list(Node* head) {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    Tuple tuple;
    tuple.list = create_node(1);
    tuple.list->next = create_node(2);
    tuple.list->next->next = create_node(3);

    Node* copied_list = copy_list_from_tuple(&tuple);

    Node* current = copied_list;
    while (current) {
        printf("%d\n", current->data);
        current = current->next;
    }

    free_list(tuple.list);
    free_list(copied_list);

    return EXIT_SUCCESS;
}