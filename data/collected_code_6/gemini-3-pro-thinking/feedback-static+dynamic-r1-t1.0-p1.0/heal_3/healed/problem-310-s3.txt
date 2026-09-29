#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;

void free_tuple(Tuple *tuple);
Tuple* string_to_tuple(const char *str);
void print_tuple(const Tuple *tuple);

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
        if (!tuple->elements[i]) {
            tuple->count = i;
            free_tuple(tuple);
            return NULL;
        }
        tuple->elements[i][0] = str[i];
        tuple->elements[i][1] = '\0';
    }

    return tuple;
}

void print_tuple(const Tuple *tuple) {
    if (!tuple) {
        return;
    }
    printf("[");
    for (size_t i = 0; i < tuple->count; i++) {
        printf("'%s'", tuple->elements[i]);
        if (i < tuple->count - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    size_t capacity = 128;
    size_t len = 0;
    char *buffer = (char *)malloc(capacity);
    
    if (!buffer) {
        return EXIT_FAILURE;
    }

    int ch;
    while ((ch = fgetc(stdin)) != EOF) {
        if (ch == '\n' || ch == '\r') {
            break;
        }
        buffer[len++] = (char)ch;
        
        if (len >= capacity - 1) {
            capacity *= 2;
            char *new_buffer = (char *)realloc(buffer, capacity);
            if (!new_buffer) {
                free(buffer);
                return EXIT_FAILURE;
            }
            buffer = new_buffer;
        }
    }
    buffer[len] = '\0';

    if (len == 0 && ch == EOF) {
        free(buffer);
        return EXIT_SUCCESS;
    }

    Tuple *tuple = string_to_tuple(buffer);
    if (tuple) {
        print_tuple(tuple);
        free_tuple(tuple);
    } else {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    return EXIT_SUCCESS;
}