#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <ctype.h>

typedef struct {
    double *values;
    size_t count;
} FloatTuple;

static int float_tuple_init(FloatTuple *tuple)
{
    if (tuple == NULL) {
        return -1;
    }
    tuple->values = NULL;
    tuple->count = 0;
    return 0;
}

static void float_tuple_free(FloatTuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->values);
        tuple->values = NULL;
        tuple->count = 0;
    }
}

static int float_tuple_append(FloatTuple *tuple, double value)
{
    double *tmp;
    size_t new_count;

    if (tuple == NULL) {
        return -1;
    }
    if (tuple->count == SIZE_MAX / sizeof(double)) {
        return -1;
    }
    new_count = tuple->count + 1U;
    tmp = realloc(tuple->values, new_count * sizeof(double));
    if (tmp == NULL) {
        return -1;
    }
    tuple->values = tmp;
    tuple->values[tuple->count] = value;
    tuple->count = new_count;
    return 0;
}

static int string_to_float_tuple(const char *input, FloatTuple *tuple)
{
    const char *cursor;
    char *endptr;

    if (input == NULL || tuple == NULL) {
        return -1;
    }
    if (float_tuple_init(tuple) != 0) {
        return -1;
    }

    cursor = input;
    while (*cursor != '\0') {
        double value;

        while (*cursor != '\0' &&
               (isspace((unsigned char)*cursor) || *cursor == ',')) {
            cursor++;
        }
        if (*cursor == '\0') {
            break;
        }

        errno = 0;
        endptr = NULL;
        value = strtod(cursor, &endptr);

        if (endptr == cursor) {
            float_tuple_free(tuple);
            return -1;
        }
        if (errno == ERANGE) {
            float_tuple_free(tuple);
            return -1;
        }
        if (float_tuple_append(tuple, value) != 0) {
            float_tuple_free(tuple);
            return -1;
        }
        cursor = endptr;
    }

    if (tuple->count == 0) {
        return -1;
    }
    return 0;
}

static void float_tuple_print(const FloatTuple *tuple)
{
    size_t i;

    if (tuple == NULL || tuple->values == NULL) {
        return;
    }
    if (fputs("(", stdout) == EOF) {
        return;
    }
    for (i = 0; i < tuple->count; i++) {
        if (printf("%g", tuple->values[i]) < 0) {
            return;
        }
        if (i + 1U < tuple->count) {
            if (fputs(", ", stdout) == EOF) {
                return;
            }
        }
    }
    if (puts(")") == EOF) {
        return;
    }
}

int main(void)
{
    const char *test_input = "1.2, 3.45, -6.78, 0.001, 99.9";
    FloatTuple tuple;

    if (string_to_float_tuple(test_input, &tuple) != 0) {
        if (fputs("Conversion failed\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    float_tuple_print(&tuple);
    float_tuple_free(&tuple);

    return EXIT_SUCCESS;
}