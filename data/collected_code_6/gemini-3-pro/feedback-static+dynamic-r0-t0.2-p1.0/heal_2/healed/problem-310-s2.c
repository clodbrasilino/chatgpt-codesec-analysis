#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;

Tuple* string_to_tuple(const char *str, const char *delimiter) {
    if (!str || !delimiter) {
        return NULL;
    }

    Tuple *tuple = malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }

    tuple->elements = NULL;
    tuple->count = 0;

    if (delimiter[0] == '\0') {
        size_t len = 0;
        while (str[len] != '\0') {
            len++;
        }
        
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
        return tuple;
    }

    char *str_copy = strdup(str);
    if (!str_copy) {
        free(tuple);
        return NULL;
    }

    char *saveptr;
    char *token = strtok_r(str_copy, delimiter, &saveptr);

    while (token != NULL) {
        char **new_elements = realloc(tuple->elements, (tuple->count + 1) * sizeof(char *));
        if (!new_elements) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->elements[i]);
            }
            free(tuple->elements);
            free(tuple);
            free(str_copy);
            return NULL;
        }
        tuple->elements = new_elements;

        tuple->elements[tuple->count] = strdup(token);
        if (!tuple->elements[tuple->count]) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->elements[i]);
            }
            free(tuple->elements);
            free(tuple);
            free(str_copy);
            return NULL;
        }
        tuple->count++;

        token = strtok_r(NULL, delimiter, &saveptr);
    }

    free(str_copy);
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->elements[i]);
        }
        free(tuple->elements);
        free(tuple);
    }
}

int main(int argc, char *argv[]) {
    const char *input_string = (argc > 1) ? argv[1] : "python3.0";
    const char *delimiter = (argc > 2) ? argv[2] : "";

    Tuple *my_tuple = string_to_tuple(input_string, delimiter);

    if (my_tuple) {
        printf("[");
        for (size_t i = 0; i < my_tuple->count; i++) {
            printf("'%s'", my_tuple->elements[i]);
            if (i < my_tuple->count - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free_tuple(my_tuple);
    } else {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}