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

    tuple->elements = NULL;
    tuple->count = 0;

    size_t len = strlen(str);

    if (len > 0) {
        tuple->elements = (char **)malloc(len * sizeof(char *));
        if (!tuple->elements) {
            free(tuple);
            return NULL;
        }
        
        for (size_t i = 0; i < len; i++) {
            tuple->elements[i] = (char *)malloc(2);
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
            tuple->count++;
        }
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

int main(int argc, char *argv[]) {
    char *buffer = NULL;
    int needs_free = 0;
    
    if (argc > 1) {
        buffer = argv[1];
    } else {
        size_t length = 0;
        size_t capacity = 1024;
        buffer = (char *)malloc(capacity);
        if (!buffer) {
            return EXIT_FAILURE;
        }
        needs_free = 1;
        
        int c;
        while ((c = fgetc(stdin)) != EOF && c != '\n' && c != '\r') {
            buffer[length++] = (char)c;
            if (length + 1 >= capacity) {
                capacity *= 2;
                char *new_buffer = (char *)realloc(buffer, capacity);
                if (!new_buffer) {
                    free(buffer);
                    return EXIT_FAILURE;
                }
                buffer = new_buffer;
            }
        }
        buffer[length] = '\0';
        
        if (length == 0 && feof(stdin)) {
            free(buffer);
            return EXIT_SUCCESS;
        }
    }

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
    } else {
        if (needs_free) {
            free(buffer);
        }
        return EXIT_FAILURE;
    }

    if (needs_free) {
        free(buffer);
    }
    
    return EXIT_SUCCESS;
}