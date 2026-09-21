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

    size_t len = strlen(str);
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
    char *input_string = NULL;

    if (argc > 1) {
        input_string = strdup(argv[1]);
        if (!input_string) {
            return EXIT_FAILURE;
        }
    } else {
        size_t capacity = 1024;
        size_t len = 0;
        int ch;
        
        input_string = malloc(capacity);
        if (!input_string) {
            return EXIT_FAILURE;
        }
        
        while ((ch = getchar()) != EOF && ch != '\n' && ch != '\r') {
            input_string[len++] = (char)ch;
            if (len >= capacity - 1) {
                capacity *= 2;
                char *temp = realloc(input_string, capacity);
                if (!temp) {
                    free(input_string);
                    return EXIT_FAILURE;
                }
                input_string = temp;
            }
        }
        input_string[len] = '\0';
    }

    Tuple *tuple = string_to_tuple(input_string);
    if (!tuple) {
        free(input_string);
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
    free(input_string);
    
    return EXIT_SUCCESS;
}