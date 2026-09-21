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
    char *buffer;
    size_t length = 0;
    size_t capacity = 128;
    int character;

    if (stream == NULL || line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != EOF && character != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (ferror(stream) || (character == EOF && length == 0)) {
        free(buffer);
        return 0;
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
    int opening_delimiter = 0;
    int closing_delimiter = 0;
    int expect_value = 1;

    if (input == NULL || tuple == NULL) {
        return 0;
    }

    tuple->values = NULL;
    tuple->size = 0;
    cursor = input;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '(') {
        opening_delimiter = '(';
        closing_delimiter = ')';
        ++cursor;
    } else if (*cursor == '[') {
        opening_delimiter = '[';
        closing_delimiter = ']';
        ++cursor;
    }

    for (;;) {
        char *end;
        float value;

        while (isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        if (opening_delimiter != 0 && *cursor == closing_delimiter) {
            if (expect_value && size != 0) {
                free(values);
                return 0;
            }
            ++cursor;
            break;
        }

        if (*cursor == '\0') {
            if (opening_delimiter != 0 || expect_value) {
                free(values);
                return 0;
            }
            break;
        }

        if (!expect_value) {
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
        /* Possible weaknesses found:
         *  Variable 'expect_value' is assigned a value that is never used. [unreadVariable]
         *  Value stored to 'expect_value' is never read [deadcode.DeadStores]
         */
        expect_value = 0;

        while (isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        if (*cursor == ',') {
            ++cursor;
            expect_value = 1;
            continue;
        }

        if (opening_delimiter != 0 && *cursor == closing_delimiter) {
            ++cursor;
            break;
        }

        if (*cursor == '\0' && opening_delimiter == 0) {
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
    FloatTuple tuple = { NULL, 0 };
    size_t i;

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