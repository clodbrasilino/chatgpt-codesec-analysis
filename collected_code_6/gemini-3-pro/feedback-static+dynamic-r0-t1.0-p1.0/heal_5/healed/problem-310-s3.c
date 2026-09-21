#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;

Tuple* string_to_tuple(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (input[len] != '\0') {
        len++;
    }
    
    while (len > 0 && (input[len - 1] == '\n' || input[len - 1] == '\r')) {
        len--;
    }

    Tuple *tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->count = len;
    if (tuple->count == 0) {
        tuple->elements = NULL;
        return tuple;
    }

    tuple->elements = (char**)malloc(tuple->count * sizeof(char*));
    if (tuple->elements == NULL) {
        free(tuple);
        return NULL;
    }

    for (size_t i = 0; i < tuple->count; i++) {
        tuple->elements[i] = (char*)malloc(2 * sizeof(char));
        if (tuple->elements[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple->elements[j]);
            }
            free(tuple->elements);
            free(tuple);
            return NULL;
        }
        tuple->elements[i][0] = input[i];
        tuple->elements[i][1] = '\0';
    }

    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        if (tuple->elements != NULL) {
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
    char *input_str = (char*)malloc(capacity);
    if (!input_str) {
        return 1;
    }
    
    int c;
    while ((c = getchar()) != EOF) {
        if (c == '\n' || c == '\r') {
            break;
        }
        input_str[length++] = (char)c;
        if (length + 1 >= capacity) {
            capacity *= 2;
            char *temp = (char*)realloc(input_str, capacity);
            if (!temp) {
                free(input_str);
                return 1;
            }
            input_str = temp;
        }
    }
    
    if (length == 0 && c == EOF) {
        free(input_str);
        return 0;
    }
    
    input_str[length] = '\0';

    Tuple *my_tuple = string_to_tuple(input_str);
    
    if (my_tuple != NULL) {
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
    
    free(input_str);
    return 0;
}