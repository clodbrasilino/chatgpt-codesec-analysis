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

    Tuple *tuple = malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }

    size_t len = strlen(str);
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

void print_tuple(Tuple *tuple) {
    if (!tuple) return;
    printf("[");
    for (size_t i = 0; i < tuple->count; i++) {
        printf("'%s'", tuple->elements[i]);
        if (i < tuple->count - 1) {
            printf(", ");
        }
    }
    printf("]\n");
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
    size_t cap = 128;
    size_t len = 0;
    char *buffer = malloc(cap);
    if (!buffer) {
        return 1;
    }

    int c;
    while ((c = fgetc(stdin)) != EOF && c != '\n' && c != '\r') {
        if (len >= cap - 1) {
            cap *= 2;
            char *new_buffer = realloc(buffer, cap);
            if (!new_buffer) {
                free(buffer);
                return 1;
            }
            buffer = new_buffer;
        }
        buffer[len++] = (char)c;
    }
    buffer[len] = '\0';

    if (len > 0 || c != EOF) {
        Tuple *t = string_to_tuple(buffer);
        if (t) {
            print_tuple(t);
            free_tuple(t);
        }
    }

    free(buffer);
    return 0;
}