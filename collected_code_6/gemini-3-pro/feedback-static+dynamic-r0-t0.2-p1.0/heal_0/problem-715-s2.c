#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int *elements;
    size_t size;
} IntTuple;

IntTuple* string_to_tuple(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    IntTuple *tuple = (IntTuple *)malloc(sizeof(IntTuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->size = 0;
    tuple->elements = NULL;

    size_t capacity = 0;
    const char *ptr = str;

    while (*ptr != '\0') {
        while (*ptr != '\0' && !isdigit((unsigned char)*ptr) && *ptr != '-') {
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

        if (tuple->size >= capacity) {
            capacity = capacity == 0 ? 4 : capacity * 2;
            int *new_elements = (int *)realloc(tuple->elements, capacity * sizeof(int));
            if (new_elements == NULL) {
                free(tuple->elements);
                free(tuple);
                return NULL;
            }
            tuple->elements = new_elements;
        }

        tuple->elements[tuple->size++] = (int)val;
        ptr = endptr;
    }

    return tuple;
}

void free_tuple(IntTuple *tuple) {
    if (tuple != NULL) {
        free(tuple->elements);
        free(tuple);
    }
}

int main(void) {
    const char *input = "12, 34, -56, 78, 90";
    IntTuple *tuple = string_to_tuple(input);

    if (tuple != NULL) {
        printf("Tuple elements: ");
        for (size_t i = 0; i < tuple->size; i++) {
            printf("%d ", tuple->elements[i]);
        }
        printf("\n");

        free_tuple(tuple);
    } else {
        printf("Failed to parse string or allocate memory.\n");
    }

    return 0;
}