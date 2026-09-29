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
    size_t capacity = 128;

    if (stream == NULL || line == NULL) {
        return -1;
    }

    *line = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(buffer);
            return -1;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
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

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

static int append_float(float **values, size_t *size, size_t *capacity,
                        float value)
{
    if (values == NULL || size == NULL || capacity == NULL ||
        *size > *capacity) {
        return -1;
    }

    if (*size == *capacity) {
        size_t new_capacity;
        float *resized;

        if (*capacity == 0) {
            new_capacity = 4;
        } else {
            if (*capacity > SIZE_MAX / 2) {
                return -1;
            }
            new_capacity = *capacity * 2;
        }

        if (new_capacity > SIZE_MAX / sizeof **values) {
            return -1;
        }

        resized = realloc(*values, new_capacity * sizeof **values);
        if (resized == NULL) {
            return -1;
        }

        *values = resized;
        *capacity = new_capacity;
    }

    (*values)[*size] = value;
    ++*size;
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
        char *end = NULL;
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

        if (append_float(&values, &size, &capacity, value) != 0) {
            free(values);
            return -1;
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
                (closing != '\0' && *cursor == closing)) {
                free(values);
                return -1;
            }
        } else if (closing != '\0') {
            if (*cursor != closing) {
                free(values);
                return -1;
            }
        } else if (*cursor != '\0') {
            free(values);
            return -1;
        }
    }

    if (closing != '\0') {
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
    FloatTuple tuple = {NULL, 0};
    int status = EXIT_FAILURE;

    if (read_line(stdin, &input) != 0) {
        fputs("Failed to read input\n", stderr);
        goto cleanup;
    }

    if (convert_to_float_tuple(input, &tuple) != 0) {
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

        if (printf("%g", (double)tuple.values[i]) < 0) {
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