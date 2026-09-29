#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float *elements;
    size_t size;
} FloatTuple;

FloatTuple string_to_float_tuple(const char *str) {
    FloatTuple tuple = {NULL, 0};
    
    if (str == NULL) {
        return tuple;
    }

    char *str_copy = strdup(str);
    if (str_copy == NULL) {
        return tuple;
    }

    size_t capacity = 10;
    tuple.elements = (float *)malloc(capacity * sizeof(float));
    if (tuple.elements == NULL) {
        free(str_copy);
        return tuple;
    }

    char *saveptr;
    char *token = strtok_r(str_copy, " ,()[]", &saveptr);

    while (token != NULL) {
        if (tuple.size >= capacity) {
            size_t new_capacity = capacity * 2;
            float *temp = (float *)realloc(tuple.elements, new_capacity * sizeof(float));
            if (temp == NULL) {
                free(tuple.elements);
                free(str_copy);
                tuple.elements = NULL;
                tuple.size = 0;
                return tuple;
            }
            tuple.elements = temp;
            capacity = new_capacity;
        }

        char *endptr;
        float value = strtof(token, &endptr);
        
        if (endptr != token) {
            tuple.elements[tuple.size++] = value;
        }
        
        token = strtok_r(NULL, " ,()[]", &saveptr);
    }

    free(str_copy);
    return tuple;
}

void free_float_tuple(FloatTuple *tuple) {
    if (tuple != NULL && tuple->elements != NULL) {
        free(tuple->elements);
        tuple->elements = NULL;
        tuple->size = 0;
    }
}

int main() {
    const char *input = "(1.1, 2.2, 3.3, 4.4)";
    FloatTuple tuple = string_to_float_tuple(input);

    if (tuple.elements != NULL) {
        for (size_t i = 0; i < tuple.size; ++i) {
            printf("%f\n", tuple.elements[i]);
        }
    }

    free_float_tuple(&tuple);
    return 0;
}