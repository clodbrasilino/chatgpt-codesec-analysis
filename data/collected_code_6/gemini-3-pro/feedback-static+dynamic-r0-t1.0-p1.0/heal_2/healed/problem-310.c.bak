#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;

Tuple* string_to_tuple(const char *str, const char *delimiter) {
    if (!str) {
        return NULL;
    }

    Tuple *tuple = malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }

    tuple->elements = NULL;
    tuple->count = 0;

    if (!delimiter || strlen(delimiter) == 0) {
        size_t len = strlen(str);
        if (len > 0) {
            tuple->elements = malloc(len * sizeof(char *));
            if (!tuple->elements) {
                free(tuple);
                return NULL;
            }
            tuple->count = len;
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

    char *str_copy = strdup(str);
    if (!str_copy) {
        free(tuple);
        return NULL;
    }

    char *saveptr = NULL;
    char *token = strtok_r(str_copy, delimiter, &saveptr);

    while (token) {
        char **new_elements = realloc(tuple->elements, (tuple->count + 1) * sizeof(char *));
        if (!new_elements) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->elements[i]);
            }
            free(tuple->elements);
            free(str_copy);
            free(tuple);
            return NULL;
        }
        tuple->elements = new_elements;

        tuple->elements[tuple->count] = strdup(token);
        if (!tuple->elements[tuple->count]) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->elements[i]);
            }
            free(tuple->elements);
            free(str_copy);
            free(tuple);
            return NULL;
        }

        tuple->count++;
        token = strtok_r(NULL, delimiter, &saveptr);
    }

    free(str_copy);
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (!tuple) {
        return;
    }
    for (size_t i = 0; i < tuple->count; i++) {
        free(tuple->elements[i]);
    }
    free(tuple->elements);
    free(tuple);
}

int main() {
    const char *input_string = "python3.0";
    const char *delimiter = NULL;

    Tuple *tuple = string_to_tuple(input_string, delimiter);
    if (!tuple) {
        fprintf(stderr, "Failed to create tuple.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < tuple->count; i++) {
        printf("Element %zu: %s\n", i, tuple->elements[i]);
    }

    free_tuple(tuple);

    return EXIT_SUCCESS;
}