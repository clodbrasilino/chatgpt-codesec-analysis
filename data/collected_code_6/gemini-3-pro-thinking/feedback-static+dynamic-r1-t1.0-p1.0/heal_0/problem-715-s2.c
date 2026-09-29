#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

typedef struct {
    int *elements;
    size_t count;
} IntTuple;

int convert_string_to_tuple(const char *input, IntTuple *out_tuple) {
    if (!input || !out_tuple) {
        return 0;
    }

    size_t capacity = 4;
    int *data = malloc(capacity * sizeof(int));
    if (!data) {
        return 0;
    }

    size_t count = 0;
    const char *ptr = input;
    char *endptr = NULL;

    while (*ptr != '\0') {
        while (isspace((unsigned char)*ptr) || *ptr == ',') {
            ptr++;
        }
        if (*ptr == '\0') {
            break;
        }

        errno = 0;
        long val = strtol(ptr, &endptr, 10);

        if (ptr == endptr) {
            free(data);
            return 0;
        }

        if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
            free(data);
            return 0;
        }

        if (count == capacity) {
            size_t new_capacity = capacity * 2;
            int *new_data = realloc(data, new_capacity * sizeof(int));
            if (!new_data) {
                free(data);
                return 0;
            }
            data = new_data;
            capacity = new_capacity;
        }

        data[count++] = (int)val;
        ptr = endptr;
    }

    if (count == 0) {
        free(data);
        out_tuple->elements = NULL;
        out_tuple->count = 0;
        return 1;
    }

    int *final_data = realloc(data, count * sizeof(int));
    if (!final_data) {
        out_tuple->elements = data;
    } else {
        out_tuple->elements = final_data;
    }
    
    out_tuple->count = count;
    return 1;
}

void free_tuple(IntTuple *tuple) {
    if (tuple) {
        free(tuple->elements);
        tuple->elements = NULL;
        tuple->count = 0;
    }
}

int main(void) {
    const char *input_str = "15, 42, -8, 100, 0, 9999";
    IntTuple tuple = {NULL, 0};

    if (convert_string_to_tuple(input_str, &tuple)) {
        printf("Tuple elements: ");
        for (size_t i = 0; i < tuple.count; i++) {
            printf("%d ", tuple.elements[i]);
        }
        printf("\n");
        free_tuple(&tuple);
    } else {
        fprintf(stderr, "Failed to convert string to tuple.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}