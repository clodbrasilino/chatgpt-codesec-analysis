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
    if (tuple == NULL) {
        return;
    }

    free(tuple->values);
    tuple->values = NULL;
    tuple->size = 0;
}

static int read_line(FILE *stream, char **line)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 128;

    if (stream == NULL || line == NULL) {
        return 0;
    }

    *line = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        int character = fgetc(stream);

        if (character == '\n') {
            break;
        }

        if (character == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (length >= capacity - 1) {
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

        buffer[length++] = (char)(unsigned char)character;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int append_float(float **values, size_t *size, size_t *capacity,
                        float value)
{
    size_t new_capacity;
    float *new_values;

    if (values == NULL || size == NULL || capacity == NULL ||
        *size > *capacity) {
        return 0;
    }

    if (*size == *capacity) {
        if (*capacity == 0) {
            new_capacity = 4;
        } else {
            if (*capacity > SIZE_MAX / 2) {
                return 0;
            }
            new_capacity = *capacity * 2;
        }

        if (new_capacity > SIZE_MAX / sizeof **values) {
            return 0;
        }

        new_values = realloc(*values, new_capacity * sizeof **values);
        if (new_values == NULL) {
            return 0;
        }

        *values = new_values;
        *capacity = new_capacity;
    }

    (*values)[*size] = value;
    ++*size;
    return 1;
}

static int string_to_float_tuple(const char *input, FloatTuple *tuple)
{
    const char *cursor;
    float *values = NULL;
    size_t size = 0;
    size_t capacity = 0;
    char closing_delimiter = '\0';

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
        closing_delimiter = ')';
        ++cursor;
    } else if (*cursor == '[') {
        closing_delimiter = ']';
        ++cursor;
    }

    for (;;) {
        char *end = NULL;
        float value;

        while (isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        if (*cursor == '\0' ||
            (closing_delimiter != '\0' &&
             *cursor == closing_delimiter)) {
            free(values);
            return 0;
        }

        errno = 0;
        value = strtof(cursor, &end);

        if (end == cursor || errno == ERANGE || !isfinite(value)) {
            free(values);
            return 0;
        }

        if (!append_float(&values, &size, &capacity, value)) {
            free(values);
            return 0;
        }

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
                (closing_delimiter != '\0' &&
                 *cursor == closing_delimiter)) {
                free(values);
                return 0;
            }

            continue;
        }

        if (closing_delimiter != '\0') {
            if (*cursor != closing_delimiter) {
                free(values);
                return 0;
            }
            ++cursor;
        } else if (*cursor != '\0') {
            free(values);
            return 0;
        }

        break;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
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
    int status = EXIT_FAILURE;

    if (!read_line(stdin, &input)) {
        fputs("Failed to read input\n", stderr);
        goto cleanup;
    }

    if (!string_to_float_tuple(input, &tuple)) {
        fputs("Invalid float tuple\n", stderr);
        goto cleanup;
    }

    if (putchar('(') == EOF) {
        goto cleanup;
    }

    for (size_t i = 0; i < tuple.size; ++i) {
        if (i != 0 && fputs(", ", stdout) == EOF) {
            goto cleanup;
        }

        if (printf("%.9g", (double)tuple.values[i]) < 0) {
            goto cleanup;
        }
    }

    if (puts(")") == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    free_float_tuple(&tuple);
    return status;
}