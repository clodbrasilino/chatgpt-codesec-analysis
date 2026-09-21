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

    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    tuple->count = len;

    if (tuple->count > 0) {
        tuple->elements = (char **)malloc(tuple->count * sizeof(char *));
        if (!tuple->elements) {
            free(tuple);
            return NULL;
        }
        for (size_t i = 0; i < tuple->count; i++) {
            tuple->elements[i] = (char *)malloc(2 * sizeof(char));
            if (!tuple->elements[i]) {
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
    } else {
        tuple->elements = NULL;
    }
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

int main(void) {
    size_t capacity = 1024;
    char *buffer = (char *)malloc(capacity);
    if (!buffer) {
        return 1;
    }

    size_t len = 0;
    int ch;
    
    while ((ch = fgetc(stdin)) != EOF && ch != '\n' && ch != '\r') {
        buffer[len++] = (char)ch;
        if (len >= capacity - 1) {
            capacity *= 2;
            char *new_buffer = (char *)realloc(buffer, capacity);
            if (!new_buffer) {
                free(buffer);
                return 1;
            }
            buffer = new_buffer;
        }
    }
    buffer[len] = '\0';

    Tuple *my_tuple = string_to_tuple(buffer);

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
    }

    free(buffer);
    return 0;
}