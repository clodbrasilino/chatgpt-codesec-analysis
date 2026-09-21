#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

typedef struct {
    int *elements;
    size_t count;
} IntTuple;

IntTuple parse_tuple(const char *str) {
    IntTuple tuple = {NULL, 0};
    if (str == NULL) {
        return tuple;
    }

    size_t len = 0;
    const char *p = str;
    while (*p != '\0') {
        if (len == SIZE_MAX) {
            return tuple;
        }
        len++;
        p++;
    }

    size_t buffer_size;
    if (__builtin_add_overflow(len, 1, &buffer_size)) {
        return tuple;
    }

    char *buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) {
        return tuple;
    }

    memcpy(buffer, str, len);
    buffer[len] = '\0';

    size_t capacity = 1;
    tuple.elements = (int *)malloc(capacity * sizeof(int));
    if (tuple.elements == NULL) {
        free(buffer);
        return tuple;
    }

    char *token = strtok(buffer, "(), ");
    while (token != NULL) {
        if (tuple.count >= capacity) {
            size_t new_capacity;
            if (__builtin_mul_overflow(capacity, 2, &new_capacity)) {
                free(tuple.elements);
                free(buffer);
                tuple.elements = NULL;
                tuple.count = 0;
                return tuple;
            }
            capacity = new_capacity;

            size_t new_size;
            if (__builtin_mul_overflow(capacity, sizeof(int), &new_size)) {
                free(tuple.elements);
                free(buffer);
                tuple.elements = NULL;
                tuple.count = 0;
                return tuple;
            }

            int *temp = (int *)realloc(tuple.elements, new_size);
            if (temp == NULL) {
                free(tuple.elements);
                free(buffer);
                tuple.elements = NULL;
                tuple.count = 0;
                return tuple;
            }
            tuple.elements = temp;
        }

        char *endptr;
        errno = 0;
        long val = strtol(token, &endptr, 10);
        if (errno == ERANGE || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
            free(tuple.elements);
            free(buffer);
            tuple.elements = NULL;
            tuple.count = 0;
            return tuple;
        }

        tuple.elements[tuple.count++] = (int)val;
        token = strtok(NULL, "(), ");
    }

    free(buffer);

    if (tuple.count == 0) {
        free(tuple.elements);
        tuple.elements = NULL;
    } else {
        size_t final_size;
        if (!__builtin_mul_overflow(tuple.count, sizeof(int), &final_size)) {
            int *shrunk = (int *)realloc(tuple.elements, final_size);
            if (shrunk != NULL) {
                tuple.elements = shrunk;
            }
        }
    }

    return tuple;
}

int main(void) {
    const char *input = "(10, 20, 30)";
    IntTuple result = parse_tuple(input);

    if (result.elements != NULL) {
        printf("(");
        for (size_t i = 0; i < result.count; i++) {
            printf("%d", result.elements[i]);
            if (i < result.count - 1) {
                printf(", ");
            }
        }
        printf(")\n");
        free(result.elements);
    }

    return 0;
}