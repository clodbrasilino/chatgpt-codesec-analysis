#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float *values;
    size_t size;
} FloatTuple;

static void free_float_tuple(FloatTuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->values);
        tuple->values = NULL;
        tuple->size = 0;
    }
}

static int string_to_float_tuple(const char *input, FloatTuple *tuple)
{
    const char *cursor;
    float *values = NULL;
    size_t size = 0;
    size_t capacity = 0;

    if (input == NULL || tuple == NULL) {
        return 0;
    }

    tuple->values = NULL;
    tuple->size = 0;
    cursor = input;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '(' || *cursor == '[') {
        ++cursor;
    }

    for (;;) {
        char *end;
        float value;

        while (isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        if (*cursor == ')' || *cursor == ']') {
            ++cursor;
            break;
        }

        if (*cursor == '\0') {
            break;
        }

        errno = 0;
        value = strtof(cursor, &end);

        if (end == cursor || errno == ERANGE || !isfinite(value)) {
            free(values);
            return 0;
        }

        if (size == capacity) {
            size_t new_capacity = capacity == 0 ? 4 : capacity * 2;
            float *new_values;

            if (new_capacity < capacity ||
                new_capacity > SIZE_MAX / sizeof(*values)) {
                free(values);
                return 0;
            }

            new_values = realloc(values, new_capacity * sizeof(*values));
            if (new_values == NULL) {
                free(values);
                return 0;
            }

            values = new_values;
            capacity = new_capacity;
        }

        values[size++] = value;
        cursor = end;

        while (isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        if (*cursor == ',') {
            ++cursor;
            continue;
        }

        if (*cursor == ')' || *cursor == ']') {
            ++cursor;
            break;
        }

        if (*cursor == '\0') {
            break;
        }

        free(values);
        return 0;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0' || size == 0) {
        free(values);
        return 0;
    }

    tuple->values = values;
    tuple->size = size;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    FloatTuple tuple;
    size_t i;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (string_to_float_tuple(input, &tuple) == 0) {
        fputs("Invalid float tuple\n", stderr);
        return EXIT_FAILURE;
    }

    putchar('(');
    for (i = 0; i < tuple.size; ++i) {
        if (i != 0) {
            fputs(", ", stdout);
        }
        printf("%.9g", (double)tuple.values[i]);
    }
    puts(")");

    free_float_tuple(&tuple);
    return EXIT_SUCCESS;
}