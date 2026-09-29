#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char** elements;
    size_t count;
} Tuple;

Tuple* string_to_tuple(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    Tuple* tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->count = strlen(str);
    if (tuple->count == 0) {
        tuple->elements = NULL;
        return tuple;
    }

    tuple->elements = malloc(tuple->count * sizeof(char*));
    if (tuple->elements == NULL) {
        free(tuple);
        return NULL;
    }

    for (size_t i = 0; i < tuple->count; i++) {
        tuple->elements[i] = malloc(2 * sizeof(char));
        if (tuple->elements[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple->elements[j]);
            }
            free(tuple->elements);
            free(tuple);
            return NULL;
        }
        tuple->elements[i][0] = str[i];
        tuple->elements[i][1] = '\0';
    }

    return tuple;
}

void free_tuple(Tuple* tuple) {
    if (tuple != NULL) {
        if (tuple->elements != NULL) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->elements[i]);
            }
            free(tuple->elements);
        }
        free(tuple);
    }
}

int main() {
    const char* str = "python3.0";
    Tuple* tuple = string_to_tuple(str);

    if (tuple != NULL) {
        for (size_t i = 0; i < tuple->count; i++) {
            printf("Element %zu: %s\n", i, tuple->elements[i]);
        }
        free_tuple(tuple);
    } else {
        printf("Failed to parse tuple.\n");
    }

    return 0;
}