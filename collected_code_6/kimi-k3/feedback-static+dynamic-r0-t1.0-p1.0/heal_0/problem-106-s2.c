#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t size;
    size_t capacity;
} IntList;

typedef struct {
    int *elements;
    size_t size;
} IntTuple;

int init_list(IntList *list, size_t initial_capacity) {
    if (list == NULL || initial_capacity == 0) {
        return -1;
    }
    list->elements = malloc(initial_capacity * sizeof(int));
    if (list->elements == NULL) {
        return -1;
    }
    list->size = 0;
    list->capacity = initial_capacity;
    return 0;
}

void free_list(IntList *list) {
    if (list != NULL && list->elements != NULL) {
        free(list->elements);
        list->elements = NULL;
        list->size = 0;
        list->capacity = 0;
    }
}

int init_tuple(IntTuple *tuple, size_t size) {
    if (tuple == NULL || size == 0) {
        return -1;
    }
    tuple->elements = malloc(size * sizeof(int));
    if (tuple->elements == NULL) {
        return -1;
    }
    tuple->size = size;
    return 0;
}

void free_tuple(IntTuple *tuple) {
    if (tuple != NULL && tuple->elements != NULL) {
        free(tuple->elements);
        tuple->elements = NULL;
        tuple->size = 0;
    }
}

int add_list_to_tuple(IntTuple *tuple, const IntList *list) {
    if (tuple == NULL || list == NULL || tuple->elements == NULL || list->elements == NULL) {
        return -1;
    }
    if (tuple->size != list->size) {
        return -1;
    }
    for (size_t i = 0; i < tuple->size; i++) {
        tuple->elements[i] += list->elements[i];
    }
    return 0;
}

int main(void) {
    IntList list;
    IntTuple tuple;
    size_t size = 5;

    if (init_list(&list, size) != 0) {
        fprintf(stderr, "Failed to initialize list\n");
        return EXIT_FAILURE;
    }

    if (init_tuple(&tuple, size) != 0) {
        fprintf(stderr, "Failed to initialize tuple\n");
        free_list(&list);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        list.elements[i] = (int)(i + 1);
        tuple.elements[i] = (int)((i + 1) * 10);
    }
    list.size = size;

    printf("Tuple before addition: ");
    for (size_t i = 0; i < tuple.size; i++) {
        printf("%d ", tuple.elements[i]);
    }
    printf("\n");

    if (add_list_to_tuple(&tuple, &list) != 0) {
        fprintf(stderr, "Failed to add list to tuple\n");
        free_list(&list);
        free_tuple(&tuple);
        return EXIT_FAILURE;
    }

    printf("Tuple after addition: ");
    for (size_t i = 0; i < tuple.size; i++) {
        printf("%d ", tuple.elements[i]);
    }
    printf("\n");

    free_list(&list);
    free_tuple(&tuple);

    return EXIT_SUCCESS;
}