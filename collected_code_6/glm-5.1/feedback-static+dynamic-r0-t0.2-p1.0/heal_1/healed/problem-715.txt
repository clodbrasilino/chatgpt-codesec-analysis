#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    int *elements;
    size_t size;
} IntTuple;

IntTuple *str_to_int_tuple(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
    size_t count = 0;

    if (len > 0) {
        count = 1;
        for (size_t i = 0; i < len; i++) {
            if (str[i] == ',') {
                count++;
            }
        }
    }

    IntTuple *tuple = (IntTuple *)malloc(sizeof(IntTuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->size = count;
    tuple->elements = NULL;

    if (count > 0) {
        tuple->elements = (int *)malloc(count * sizeof(int));
        if (tuple->elements == NULL) {
            free(tuple);
            return NULL;
        }

        char *buffer = (char *)malloc(len + 1);
        if (buffer == NULL) {
            free(tuple->elements);
            free(tuple);
            return NULL;
        }

        snprintf(buffer, len + 1, "%s", str);

        char *token = strtok(buffer, ",");
        size_t index = 0;

        while (token != NULL && index < count) {
            char *endptr;
            long val = strtol(token, &endptr, 10);

            if (endptr == token) {
                tuple->elements[index] = 0;
            } else if (val > INT_MAX) {
                tuple->elements[index] = INT_MAX;
            } else if (val < INT_MIN) {
                tuple->elements[index] = INT_MIN;
            } else {
                tuple->elements[index] = (int)val;
            }

            index++;
            token = strtok(NULL, ",");
        }

        free(buffer);
    }

    return tuple;
}

void free_int_tuple(IntTuple *tuple) {
    if (tuple != NULL) {
        free(tuple->elements);
        free(tuple);
    }
}

int main(void) {
    const char *input = "10,20,-5,0,42";
    IntTuple *tuple = str_to_int_tuple(input);

    if (tuple == NULL) {
        return EXIT_FAILURE;
    }

    printf("(");
    for (size_t i = 0; i < tuple->size; i++) {
        printf("%d", tuple->elements[i]);
        if (i < tuple->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");

    free_int_tuple(tuple);

    return EXIT_SUCCESS;
}