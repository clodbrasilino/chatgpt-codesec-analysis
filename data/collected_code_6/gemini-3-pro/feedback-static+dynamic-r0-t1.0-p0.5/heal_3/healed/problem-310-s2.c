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

    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }

    tuple->count = len;
    if (len == 0) {
        tuple->elements = NULL;
        return tuple;
    }

    tuple->elements = (char **)malloc(len * sizeof(char *));
    if (!tuple->elements) {
        free(tuple);
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        tuple->elements[i] = (char *)malloc(2);
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
                free(tuple->elements[i]);
            }
            free(tuple->elements);
        }
        free(tuple);
    }
}

int main(void) {
    size_t capacity = 1024;
    size_t length = 0;
    char *buffer = (char *)malloc(capacity);
    
    if (!buffer) {
        return EXIT_FAILURE;
    }

    int c;
    while ((c = getchar()) != EOF && c != '\n' && c != '\r') {
        if (length + 1 >= capacity) {
            capacity *= 2;
            char *new_buffer = (char *)realloc(buffer, capacity);
            if (!new_buffer) {
                free(buffer);
                return EXIT_FAILURE;
            }
            buffer = new_buffer;
        }
        buffer[length++] = (char)c;
    }
    buffer[length] = '\0';

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
    return EXIT_SUCCESS;
}