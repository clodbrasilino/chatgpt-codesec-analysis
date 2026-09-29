#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float *elements;
    size_t size;
} FloatTuple;

FloatTuple parse_float_tuple(const char *input) {
    FloatTuple tuple = {NULL, 0};
    if (input == NULL) {
        return tuple;
    }

    size_t capacity = 10;
    tuple.elements = (float *)malloc(capacity * sizeof(float));
    if (tuple.elements == NULL) {
        return tuple;
    }

    char *input_copy = strdup(input);
    if (input_copy == NULL) {
        free(tuple.elements);
        tuple.elements = NULL;
        return tuple;
    }

    char *token = strtok(input_copy, ", ()");
    while (token != NULL) {
        if (tuple.size >= capacity) {
            capacity *= 2;
            float *new_elements = (float *)realloc(tuple.elements, capacity * sizeof(float));
            if (new_elements == NULL) {
                free(tuple.elements);
                free(input_copy);
                tuple.elements = NULL;
                tuple.size = 0;
                return tuple;
            }
            tuple.elements = new_elements;
        }

        char *endptr;
        float value = strtof(token, &endptr);
        if (endptr != token) {
            tuple.elements[tuple.size++] = value;
        }

        token = strtok(NULL, ", ()");
    }

    free(input_copy);
    return tuple;
}

void free_tuple(FloatTuple *tuple) {
    if (tuple != NULL && tuple->elements != NULL) {
        free(tuple->elements);
        tuple->elements = NULL;
        tuple->size = 0;
    }
}

int main() {
    const char *input_string = "(1.23, 4.56, 7.89, -0.5)";
    
    FloatTuple tuple = parse_float_tuple(input_string);
    
    if (tuple.elements != NULL) {
        for (size_t i = 0; i < tuple.size; i++) {
            printf("%f ", tuple.elements[i]);
        }
        printf("\n");
    }
    
    free_tuple(&tuple);
    
    return 0;
}