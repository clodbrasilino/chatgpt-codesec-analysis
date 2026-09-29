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

    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }

    tuple->elements = NULL;
    tuple->count = 0;

    if (!delimiter || delimiter[0] == '\0') {
        size_t len = strlen(str);
        if (len > 0) {
            tuple->elements = (char **)malloc(len * sizeof(char *));
            if (!tuple->elements) {
                free(tuple);
                return NULL;
            }
            for (size_t i = 0; i < len; i++) {
                tuple->elements[i] = (char *)malloc(2 * sizeof(char));
                if (!tuple->elements[i]) {
                    for (size_t j = 0; j < i; j++) free(tuple->elements[j]);
                    free(tuple->elements);
                    free(tuple);
                    return NULL;
                }
                tuple->elements[i][0] = str[i];
                tuple->elements[i][1] = '\0';
                tuple->count++;
            }
        }
        return tuple;
    }

    char *str_copy = strdup(str);
    if (!str_copy) {
        free(tuple);
        return NULL;
    }

    char *token = strtok(str_copy, delimiter);

    while (token != NULL) {
        char **new_elements = (char **)realloc(tuple->elements, (tuple->count + 1) * sizeof(char *));
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

        token = strtok(NULL, delimiter);
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
    const char *input_string = "python3.0";
    const char *delimiter = "";

    if (argc > 1) {
        input_string = argv[1];
    }
    if (argc > 2) {
        delimiter = argv[2];
    }

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
        printf("[]\n");
    }

    return EXIT_SUCCESS;
}