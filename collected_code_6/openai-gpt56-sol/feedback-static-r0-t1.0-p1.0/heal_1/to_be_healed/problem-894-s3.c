#include <ctype.h>
#include <errno.h>
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
        tuple->size = 0U;
    }
}

static int string_to_float_tuple(const char *input, FloatTuple *tuple)
{
    const char *cursor;
    float *values = NULL;
    size_t count = 0U;
    size_t capacity = 0U;

    if (input == NULL || tuple == NULL) {
        return 0;
    }

    tuple->values = NULL;
    tuple->size = 0U;
    cursor = input;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '(') {
        return 0;
    }
    ++cursor;

    while (1) {
        char *end;
        float value;

        while (isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        if (*cursor == ')') {
            ++cursor;
            break;
        }

        errno = 0;
        value = strtof(cursor, &end);
        if (end == cursor || errno == ERANGE) {
            free(values);
            return 0;
        }
        cursor = end;

        if (count == capacity) {
            size_t new_capacity = capacity == 0U ? 4U : capacity * 2U;
            float *new_values;

            if (new_capacity < capacity ||
                new_capacity > (size_t)-1 / sizeof(*values)) {
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

        values[count++] = value;

        while (isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        if (*cursor == ',') {
            ++cursor;
            while (isspace((unsigned char)*cursor)) {
                ++cursor;
            }
            if (*cursor == ')' || *cursor == '\0') {
                free(values);
                return 0;
            }
        } else if (*cursor != ')') {
            free(values);
            return 0;
        }
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        free(values);
        return 0;
    }

    tuple->values = values;
    tuple->size = count;
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
    for (i = 0U; i < tuple.size; ++i) {
        if (i != 0U) {
            fputs(", ", stdout);
        }
        printf("%.9g", (double)tuple.values[i]);
    }
    puts(")");

    free_float_tuple(&tuple);
    return EXIT_SUCCESS;
}