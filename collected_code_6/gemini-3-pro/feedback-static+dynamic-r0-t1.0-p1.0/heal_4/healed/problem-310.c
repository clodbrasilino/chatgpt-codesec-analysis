#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;

Tuple* string_to_tuple(const char *str) {
    if (!str) {
        return NULL;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    Tuple *tuple = malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }

    tuple->count = len;
    tuple->elements = NULL;

    if (len > 0) {
        tuple->elements = malloc(len * sizeof(char *));
        if (!tuple->elements) {
            free(tuple);
            return NULL;
        }
        for (size_t i = 0; i < len; i++) {
            tuple->elements[i] = malloc(2);
            if (tuple->elements[i]) {
                tuple->elements[i][0] = str[i];
                tuple->elements[i][1] = '\0';
            }
        }
    }

    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (!tuple) {
        return;
    }
    if (tuple->elements) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->elements[i]);
        }
        free(tuple->elements);
    }
    free(tuple);
}

int main(int argc, char *argv[]) {
    char buffer[4096];
    const char *input_string = NULL;

    if (argc > 1) {
        input_string = argv[1];
    } else {
        if (fgets(buffer, sizeof(buffer), stdin)) {
            size_t len = 0;
            while (buffer[len] != '\0') {
                if (buffer[len] == '\n' || buffer[len] == '\r') {
                    buffer[len] = '\0';
                    break;
                }
                len++;
            }
            input_string = buffer;
        } else {
            return EXIT_FAILURE;
        }
    }

    Tuple *tuple = string_to_tuple(input_string);
    if (!tuple) {
        return EXIT_FAILURE;
    }

    printf("[");
    for (size_t i = 0; i < tuple->count; i++) {
        printf("'%s'", tuple->elements[i]);
        if (i < tuple->count - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    free_tuple(tuple);
    return EXIT_SUCCESS;
}