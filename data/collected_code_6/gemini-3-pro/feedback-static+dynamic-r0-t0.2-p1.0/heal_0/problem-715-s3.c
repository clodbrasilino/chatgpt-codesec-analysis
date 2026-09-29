#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int *elements;
    size_t size;
} IntTuple;

IntTuple string_to_tuple(const char *str) {
    IntTuple tuple = {NULL, 0};
    
    if (str == NULL) {
        return tuple;
    }

    size_t capacity = 10;
    tuple.elements = (int *)malloc(capacity * sizeof(int));
    if (tuple.elements == NULL) {
        return tuple;
    }

    const char *ptr = str;
    while (*ptr != '\0') {
        while (*ptr != '\0' && !isdigit((unsigned char)*ptr) && *ptr != '-' && *ptr != '+') {
            ptr++;
        }

        if (*ptr == '\0') {
            break;
        }

        char *endptr;
        long val = strtol(ptr, &endptr, 10);

        if (ptr == endptr) {
            ptr++;
            continue;
        }

        if (tuple.size >= capacity) {
            size_t new_capacity = capacity * 2;
            int *new_elements = (int *)realloc(tuple.elements, new_capacity * sizeof(int));
            if (new_elements == NULL) {
                free(tuple.elements);
                tuple.elements = NULL;
                tuple.size = 0;
                return tuple;
            }
            tuple.elements = new_elements;
            capacity = new_capacity;
        }

        tuple.elements[tuple.size++] = (int)val;
        ptr = endptr;
    }

    if (tuple.size == 0) {
        free(tuple.elements);
        tuple.elements = NULL;
    }

    return tuple;
}

void free_tuple(IntTuple *tuple) {
    if (tuple != NULL && tuple->elements != NULL) {
        free(tuple->elements);
        tuple->elements = NULL;
        tuple->size = 0;
    }
}

int main(void) {
    const char *input = "12, 34, -56, 78, 90";
    
    IntTuple tuple = string_to_tuple(input);
    
    if (tuple.elements != NULL) {
        printf("(");
        for (size_t i = 0; i < tuple.size; i++) {
            printf("%d%s", tuple.elements[i], (i < tuple.size - 1) ? ", " : "");
        }
        printf(")\n");
        
        free_tuple(&tuple);
    } else {
        printf("Failed to parse tuple or empty input.\n");
    }
    
    return 0;
}