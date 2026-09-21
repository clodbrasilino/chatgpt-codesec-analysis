#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdint.h>
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

static int read_line(FILE *stream, char **line)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch = EOF;

    if (stream == NULL || line == NULL) {
        return 0;
    }

    *line = NULL;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(buffer);
                    return 0;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity > SIZE_MAX / sizeof(*buffer)) {
                free(buffer);
                return 0;
            }

            new_buffer = realloc(buffer, new_capacity * sizeof(*buffer));
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stream) || (ch == EOF && length == 0)) {
        free(buffer);
        return 0;
    }

    if (length == SIZE_MAX) {
        free(buffer);
        return 0;
    }

    if (capacity < length + 1) {
        char *new_buffer = realloc(buffer, length + 1);

        if (new_buffer == NULL) {
            free(buffer);
            return 0;
        }

        buffer = new_buffer;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int string_to_float_tuple(const char *input, FloatTuple *tuple)
{
    const char *cursor;
    float *values = NULL;
    size_t size = 0;
    size_t capacity = 0;
    char closing = '\0';

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
        char opening = *cursor++;
        closing = opening == '(' ? ')' : ']';
    }

    for (;;) {
        char *end;
        float value;

        while (isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        if (closing != '\0' && *cursor == closing) {
            ++cursor;
            break;
        }

        if (*cursor == '\0') {
            if (closing != '\0') {
                free(values);
                return 0;
            }
            break;
        }

        if (*cursor == ')' || *cursor == ']') {
            free(values);
            return 0;
        }

        errno = 0;
        value = strtof(cursor, &end);

        if (end == cursor || errno == ERANGE || !isfinite(value)) {
            free(values);
            return 0;
        }

        if (size == capacity) {
            size_t new_capacity;
            float *new_values;

            if (capacity == 0) {
                new_capacity = 4;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(values);
                    return 0;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity > SIZE_MAX / sizeof(*values)) {
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

            while (isspace((unsigned char)*cursor)) {
                ++cursor;
            }

            if (*cursor == '\0' ||
                (closing != '\0' && *cursor == closing)) {
                free(values);
                return 0;
            }

            continue;
        }

        if (closing != '\0' && *cursor == closing) {
            ++cursor;
            break;
        }

        if (closing == '\0' && *cursor == '\0') {
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
    char *input = NULL;
    FloatTuple tuple = {NULL, 0};

    if (!read_line(stdin, &input)) {
        return EXIT_FAILURE;
    }

    if (!string_to_float_tuple(input, &tuple)) {
        free(input);
        fputs("Invalid float tuple\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    putchar('(');

    for (size_t i = 0; i < tuple.size; ++i) {
        if (i != 0) {
            fputs(", ", stdout);
        }

        printf("%.9g", (double)tuple.values[i]);
    }

    puts(")");
    free_float_tuple(&tuple);

    return EXIT_SUCCESS;
}