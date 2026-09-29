#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int type;
    void *value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int size;
} Tuple;

Tuple* create_tuple() {
    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (!tuple) return NULL;
    tuple->head = NULL;
    tuple->size = 0;
    return tuple;
}

void add_element(Tuple *tuple, int type, void *value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) return;
    new_node->type = type;
    new_node->value = value;
    new_node->next = tuple->head;
    tuple->head = new_node;
    tuple->size++;
}

void free_tuple(Tuple *tuple) {
    Node *current = tuple->head;
    while (current) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(tuple);
}

void remove_elements_by_type(Tuple *tuple, int type) {
    Node *current = tuple->head;
    Node *prev = NULL;
    while (current) {
        if (current->type == type) {
            if (prev) {
                prev->next = current->next;
                free(current);
                current = prev->next;
                tuple->size--;
            } else {
                tuple->head = current->next;
                free(current);
                current = tuple->head;
                tuple->size--;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}

int main() {
    Tuple *tuple = create_tuple();
    if (!tuple) return 1;

    int int_value = 42;
    char* string_value = "hello";
    float float_value = 3.14;

    add_element(tuple, 1, &int_value);
    add_element(tuple, 2, string_value);
    add_element(tuple, 1, &float_value);

    remove_elements_by_type(tuple, 1);

    free_tuple(tuple);
    return 0;
}