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

    IntTuple *tuple = malloc(sizeof(IntTuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->elements = NULL;
    tuple->size = 0;

    size_t capacity = 10;
    tuple->elements = malloc(capacity * sizeof(int));
    if (tuple->elements == NULL) {
        free(tuple);
        return NULL;
    }

    const char *ptr = str;
    char *endptr;

    while (*ptr != '\0') {
        while (isspace((unsigned char)*ptr) || *ptr == ',') {
            ptr++;
        }

        if (*ptr == '\0') {
            break;
        }

        long val = strtol(ptr, &endptr, 10);

        if (ptr == endptr) {
            ptr++;
            continue;
        }

        if (tuple->size >= capacity) {
            capacity *= 2;
            int *new_elements = realloc(tuple->elements, capacity * sizeof(int));
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
    const char *input = "10, 20, 30, 40, 50";
    IntTuple *tuple = string_to_tuple(input);

    if (tuple != NULL) {
        printf("Tuple elements: ");
        for (size_t i = 0; i < tuple->size; i++) {
            printf("%d ", tuple->elements[i]);
        }
        printf("\n");
        free_tuple(tuple);
    } else {
        printf("Failed to create tuple.\n");
    }

    return 0;
}