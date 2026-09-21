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
    int ch;

    if (stream == NULL || line == NULL) {
        return -1;
    }

    *line = NULL;

    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
        char *resized;
        size_t new_capacity;

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return -1;
        }

        if (length + 1 >= capacity) {
            new_capacity = capacity == 0 ? 128 : capacity * 2;

            if (new_capacity <= capacity || new_capacity > SIZE_MAX) {
                free(buffer);
                return -1;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return -1;
    }

    if (buffer == NULL) {
        buffer = malloc(1);
        if (buffer == NULL) {
            return -1;
        }
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

static int convert_to_float_tuple(const char *input, FloatTuple *result)
{
    const char *cursor;
    float *values = NULL;
    size_t size = 0;
    size_t capacity = 0;
    char closing = '\0';

    if (input == NULL || result == NULL) {
        return -1;
    }

    result->values = NULL;
    result->size = 0;
    cursor = input;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '(') {
        closing = ')';
        ++cursor;
    } else if (*cursor == '[') {
        closing = ']';
        ++cursor;
    }

    for (;;) {
        char *end;
        float value;

        while (isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        if ((closing != '\0' && *cursor == closing) ||
            (closing == '\0' && *cursor == '\0')) {
            break;
        }

        if (*cursor == '\0') {
            free(values);
            return -1;
        }

        errno = 0;
        value = strtof(cursor, &end);

        if (end == cursor || errno == ERANGE || !isfinite(value)) {
            free(values);
            return -1;
        }

        if (size == capacity) {
            size_t new_capacity;
            float *resized;

            if (capacity == 0) {
                new_capacity = 4;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(values);
                    return -1;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity > SIZE_MAX / sizeof(*values)) {
                free(values);
                return -1;
            }

            resized = realloc(values, new_capacity * sizeof(*values));
            if (resized == NULL) {
                free(values);
                return -1;
            }

            values = resized;
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

            if (*cursor == '\0' || (closing != '\0' && *cursor == closing)) {
                free(values);
                return -1;
            }
        } else if ((closing != '\0' && *cursor != closing) ||
                   (closing == '\0' && *cursor != '\0')) {
            free(values);
            return -1;
        }
    }

    if (closing != '\0') {
        if (*cursor != closing) {
            free(values);
            return -1;
        }
        ++cursor;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0' || size == 0) {
        free(values);
        return -1;
    }

    result->values = values;
    result->size = size;
    return 0;
}

int main(void)
{
    char *input = NULL;
    FloatTuple tuple = { NULL, 0 };
    size_t i;

    if (read_line(stdin, &input) != 0) {
        fputs("Failed to read input\n", stderr);
        return EXIT_FAILURE;
    }

    if (convert_to_float_tuple(input, &tuple) != 0) {
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
        printf("%g", (double)tuple.values[i]);
    }
    puts(")");

    free_float_tuple(&tuple);
    return EXIT_SUCCESS;
}