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

static int append_float(FloatTuple *tuple, size_t *capacity, float value)
{
    size_t new_capacity;
    float *resized;

    if (tuple == NULL || capacity == NULL) {
        return -1;
    }

    if (tuple->size < *capacity) {
        tuple->values[tuple->size++] = value;
        return 0;
    }

    if (*capacity == 0) {
        new_capacity = 4;
    } else {
        if (*capacity > SIZE_MAX / 2) {
            return -1;
        }
        new_capacity = *capacity * 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*tuple->values)) {
        return -1;
    }

    resized = realloc(tuple->values,
                      new_capacity * sizeof(*tuple->values));
    if (resized == NULL) {
        return -1;
    }

    tuple->values = resized;
    *capacity = new_capacity;
    tuple->values[tuple->size++] = value;
    return 0;
}

static int convert_to_float_tuple(const char *input, FloatTuple *result)
{
    const char *cursor;
    char closing = '\0';
    size_t capacity = 0;

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

        if ((closing != '\0' && *cursor == closing) || *cursor == '\0') {
            break;
        }

        if (*cursor == ')' || *cursor == ']') {
            free_float_tuple(result);
            return -1;
        }

        errno = 0;
        value = strtof(cursor, &end);

        if (end == cursor || errno == ERANGE || !isfinite(value)) {
            free_float_tuple(result);
            return -1;
        }

        if (append_float(result, &capacity, value) != 0) {
            free_float_tuple(result);
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
                free_float_tuple(result);
                return -1;
            }
        } else if ((closing != '\0' && *cursor == closing) ||
                   (closing == '\0' && *cursor == '\0')) {
            break;
        } else {
            free_float_tuple(result);
            return -1;
        }
    }

    if (closing != '\0') {
        if (*cursor != closing) {
            free_float_tuple(result);
            return -1;
        }
        ++cursor;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0' || result->size == 0) {
        free_float_tuple(result);
        return -1;
    }

    return 0;
}

static char *read_line(FILE *stream)
{
    enum { MAX_LINE_LENGTH = 1024 * 1024 };
    char *buffer;
    size_t length = 0;
    size_t capacity = 128;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (character == '\0' || length >= MAX_LINE_LENGTH) {
            free(buffer);
            return NULL;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity >= (size_t)MAX_LINE_LENGTH + 1) {
                free(buffer);
                return NULL;
            }

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2;
            if (new_capacity > (size_t)MAX_LINE_LENGTH + 1) {
                new_capacity = (size_t)MAX_LINE_LENGTH + 1;
            }

            if (new_capacity <= length + 1) {
                free(buffer);
                return NULL;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)character;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input;
    FloatTuple tuple = { NULL, 0 };
    size_t i;

    input = read_line(stdin);
    if (input == NULL) {
        fputs("Unable to read input\n", stderr);
        return EXIT_FAILURE;
    }

    if (convert_to_float_tuple(input, &tuple) != 0) {
        free(input);
        fputs("Invalid float tuple\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (putchar('(') == EOF) {
        free_float_tuple(&tuple);
        return EXIT_FAILURE;
    }

    for (i = 0; i < tuple.size; ++i) {
        if (i != 0 && fputs(", ", stdout) == EOF) {
            free_float_tuple(&tuple);
            return EXIT_FAILURE;
        }

        if (printf("%g", (double)tuple.values[i]) < 0) {
            free_float_tuple(&tuple);
            return EXIT_FAILURE;
        }
    }

    if (puts(")") == EOF) {
        free_float_tuple(&tuple);
        return EXIT_FAILURE;
    }

    free_float_tuple(&tuple);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}