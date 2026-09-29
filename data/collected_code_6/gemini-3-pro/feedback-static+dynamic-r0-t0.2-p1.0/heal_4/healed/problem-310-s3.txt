#include <stdio.h>
#include <stdlib.h>

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
    if (len == 0) {
        tuple->elements = NULL;
        return tuple;
    }
    
    tuple->elements = malloc(tuple->count * sizeof(char *));
    
    if (!tuple->elements) {
        free(tuple);
        return NULL;
    }

    for (size_t i = 0; i < tuple->count; i++) {
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

int main(void) {
    size_t capacity = 128;
    size_t length = 0;
    char *buffer = malloc(capacity);
    
    if (!buffer) {
        return EXIT_FAILURE;
    }
    
    int ch;
    while ((ch = fgetc(stdin)) != EOF && ch != '\n' && ch != '\r') {
        if (length + 1 >= capacity) {
            capacity *= 2;
            char *new_buffer = realloc(buffer, capacity);
            if (!new_buffer) {
                free(buffer);
                return EXIT_FAILURE;
            }
            buffer = new_buffer;
        }
        buffer[length++] = (char)ch;
    }
    buffer[length] = '\0';
    
    if (length > 0 || ch != EOF) {
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
    }

    free(buffer);
    return EXIT_SUCCESS;
}