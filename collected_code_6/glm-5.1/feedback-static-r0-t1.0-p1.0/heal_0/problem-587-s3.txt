#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

Tuple *convert_list_to_tuple(const int *list, size_t size) {
    if (size > 0 && list == NULL) {
        return NULL;
    }

    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    if (size == 0) {
        tuple->elements = NULL;
        tuple->size = 0;
        return tuple;
    }

    tuple->elements = (int *)malloc(size * sizeof(int));
    if (tuple->elements == NULL) {
        free(tuple);
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        tuple->elements[i] = list[i];
    }

    tuple->size = size;
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        free(tuple->elements);
        free(tuple);
    }
}

int main(void) {
    int list_data[] = {10, 20, 30, 40, 50};
    size_t list_size = sizeof(list_data) / sizeof(list_data[0]);

    Tuple *my_tuple = convert_list_to_tuple(list_data, list_size);
    if (my_tuple == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < my_tuple->size; i++) {
        printf("%d ", my_tuple->elements[i]);
    }
    printf("\n");

    free_tuple(my_tuple);

    return EXIT_SUCCESS;
}