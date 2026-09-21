#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 8192

typedef struct {
    char **elements;
    size_t count;
} Tuple;

Tuple* string_to_tuple(const char *str) {
    if (!str) return NULL;

    size_t len = 0;
    while (len < MAX_INPUT_SIZE && str[len] != '\0') {
        len++;
    }

    Tuple *tuple = malloc(sizeof(Tuple));
    if (!tuple) return NULL;

    tuple->count = len;
    if (len == 0) {
        tuple->elements = NULL;
        return tuple;
    }
    
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

    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple) {
        if (tuple->elements) {
            for (size_t i = 0; i < tuple->count; i++) {
                if (tuple->elements[i]) {
                    free(tuple->elements[i]);
                }
            }
            free(tuple->elements);
        }
        free(tuple);
    }
}

int main(int argc, char *argv[]) {
    char *buffer = malloc(MAX_INPUT_SIZE);
    if (!buffer) return EXIT_FAILURE;

    buffer[0] = '\0';

    if (argc > 1) {
        size_t i = 0;
        while (i < MAX_INPUT_SIZE - 1 && argv[1][i] != '\0') {
            buffer[i] = argv[1][i];
            i++;
        }
        buffer[i] = '\0';
    } else {
        if (!fgets(buffer, MAX_INPUT_SIZE, stdin)) {
            free(buffer);
            return EXIT_FAILURE;
        }
        size_t len = 0;
        while (buffer[len] != '\0') {
            len++;
        }
        while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
            buffer[len - 1] = '\0';
            len--;
        }
    }

    Tuple *my_tuple = string_to_tuple(buffer);
    
    if (my_tuple) {
        printf("[");
        for (size_t i = 0; i < my_tuple->count; i++) {
            printf("'%s'%s", my_tuple->elements[i], i < my_tuple->count - 1 ? ", " : "");
        }
        printf("]\n");
        free_tuple(my_tuple);
    } else {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    return EXIT_SUCCESS;
}