#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    size_t size;
} List;

Tuple *list_to_tuple(const List *list) {
    if (list == NULL) {
        return NULL;
    }

    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    if (list->size > 0) {
        tuple->elements = (int *)malloc(list->size * sizeof(int));
        if (tuple->elements == NULL) {
            free(tuple);
            return NULL;
        }

        Node *current = list->head;
        for (size_t i = 0; i < list->size; ++i) {
            if (current != NULL) {
                tuple->elements[i] = current->value;
                current = current->next;
            } else {
                tuple->size = i;
                return tuple;
            }
        }
    } else {
        tuple->elements = NULL;
    }

    tuple->size = list->size;
    return tuple;
}

void free_list(List *list) {
    if (list == NULL) {
        return;
    }
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->size = 0;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    free(tuple->elements);
    free(tuple);
}

int main(void) {
    List list = {NULL, 0};

    Node n1 = {10, NULL};
    Node n2 = {20, NULL};
    Node n3 = {30, NULL};

    list.head = &n1;
    n1.next = &n2;
    n2.next = &n3;
    list.size = 3;

    Tuple *tuple = list_to_tuple(&list);
    if (tuple == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < tuple->size; ++i) {
        printf("%d ", tuple->elements[i]);
    }
    printf("\n");

    free_tuple(tuple);

    return EXIT_SUCCESS;
}