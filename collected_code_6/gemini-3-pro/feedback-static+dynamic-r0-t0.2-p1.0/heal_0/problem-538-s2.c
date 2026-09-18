#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t size;
} Tuple;

Tuple* string_list_to_tuple(char **list, size_t size) {
    if (list == NULL || size == 0) {
        return NULL;
    }

    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->elements = (char **)malloc(size * sizeof(char *));
    if (tuple->elements == NULL) {
        free(tuple);
        return NULL;
    }

    tuple->size = size;

    for (size_t i = 0; i < size; i++) {
        if (list[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple->elements[j]);
            }
            free(tuple->elements);
            free(tuple);
            return NULL;
        }

        tuple->elements[i] = strdup(list[i]);
        if (tuple->elements[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple->elements[j]);
            }
            free(tuple->elements);
            free(tuple);
            return NULL;
        }
    }

    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        if (tuple->elements != NULL) {
            for (size_t i = 0; i < tuple->size; i++) {
                free(tuple->elements[i]);
            }
            free(tuple->elements);
        }
        free(tuple);
    }
}

int main(void) {
    char *list[] = {"apple", "banana", "cherry"};
    size_t size = sizeof(list) / sizeof(list[0]);

    Tuple *tuple = string_list_to_tuple(list, size);

    if (tuple != NULL) {
        for (size_t i = 0; i < tuple->size; i++) {
            printf("%s\n", tuple->elements[i]);
        }
        free_tuple(tuple);
    } else {
        fprintf(stderr, "Failed to create tuple.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}