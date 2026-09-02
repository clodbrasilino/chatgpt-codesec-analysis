#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int value;
    struct List *next;
} List;

typedef struct Tuple {
    int *values;
    int size;
} Tuple;

Tuple* list_to_tuple(List *list) {
    if (list == NULL) {
        return NULL;
    }

    int elements = 0;
    List *current = list;
    while (current != NULL) {
        elements++;
        current = current->next;
    }

    Tuple *tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->values = (int*)malloc(elements * sizeof(int));
    if (tuple->values == NULL) {
        free(tuple);
        return NULL;
    }

    tuple->size = elements;
    current = list;
    for (int i = 0; i < elements; i++) {
        tuple->values[i] = current->value;
        current = current->next;
    }

    return tuple;
}

void print_tuple(Tuple *tuple) {
    if (tuple == NULL || tuple->values == NULL) {
        printf("Empty tuple\n");
        return;
    }

    for (int i = 0; i < tuple->size; i++) {
        printf("%d", tuple->values[i]);
        if (i < tuple->size - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL || tuple->values == NULL) {
        return;
    }
    free(tuple->values);
    free(tuple);
}

void free_list(List *list) {
    if (list == NULL) {
        return;
    }
    List *current = list;
    List *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    List *head = (List*)malloc(sizeof(List));
    head->value = 1;
    head->next = (List*)malloc(sizeof(List));
    head->next->value = 2;
    head->next->next = (List*)malloc(sizeof(List));
    head->next->next->value = 3;
    head->next->next->next = NULL;

    Tuple *tuple = list_to_tuple(head);

    print_tuple(tuple);

    free_tuple(tuple);
    free_list(head);

    return 0;
}