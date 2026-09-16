#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    size_t length;
} IntTuple;

int string_to_int_tuple(const char *input, IntTuple *tuple) {
    const char *p;
    char *end;
    int *data;
    size_t length;
    size_t capacity;

    if (input == NULL || tuple == NULL) {
        return -1;
    }

    tuple->values = NULL;
    tuple->length = 0;

    data = NULL;
    length = 0;
    capacity = 0;
    p = input;

    while (*p != '\0') {
        while (isspace((unsigned char)*p)) {
            p++;
        }

        if (*p == '\0') {
            break;
        }

        errno = 0;
        long value = strtol(p, &end, 10);

        if (errno == ERANGE || end == p || value < INT_MIN || value > INT_MAX) {
            free(data);
            return -1;
        }

        if (*end != '\0' && !isspace((unsigned char)*end)) {
            free(data);
            return -1;
        }

        if (length == capacity) {
            size_t new_capacity = (capacity == 0) ? 4 : capacity * 2;
            int *new_data = realloc(data, new_capacity * sizeof(*new_data));

            if (new_data == NULL) {
                free(data);
                return -1;
            }

            data = new_data;
            capacity = new_capacity;
        }

        data[length] = (int)value;
        length++;
        p = end;
    }

    if (length == 0) {
        free(data);
        return -1;
    }

    tuple->values = data;
    tuple->length = length;

    return 0;
}

void destroy_int_tuple(IntTuple *tuple) {
    if (tuple == NULL) {
        return;
    }

    free(tuple->values);
    tuple->values = NULL;
    tuple->length = 0;
}

int main(void) {
    const char *input = "10 20 -30 40";
    IntTuple tuple;

    if (string_to_int_tuple(input, &tuple) != 0) {
        fprintf(stderr, "Failed to parse integer tuple\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < tuple.length; i++) {
        printf("%d\n", tuple.values[i]);
    }

    destroy_int_tuple(&tuple);

    return EXIT_SUCCESS;
}