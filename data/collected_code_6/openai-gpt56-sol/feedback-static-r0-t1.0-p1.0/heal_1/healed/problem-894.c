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
    float *resized;
    size_t new_capacity;

    if (tuple->size < *capacity) {
        tuple->values[tuple->size++] = value;
        return 0;
    }

    new_capacity = (*capacity == 0) ? 4 : *capacity;

    if (*capacity != 0) {
        if (*capacity > SIZE_MAX / 2) {
            return -1;
        }
        new_capacity = *capacity * 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*tuple->values)) {
        return -1;
    }

    resized = realloc(tuple->values, new_capacity * sizeof(*tuple->values));
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
    size_t capacity = 0;
    char opening = '\0';
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

    if (*cursor == '(' || *cursor == '[') {
        opening = *cursor++;
        closing = (opening == '(') ? ')' : ']';
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
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;

    while ((character = fgetc(stream)) != EOF && character != '\n') {
        char *resized;
        size_t new_capacity;

        if (length == capacity) {
            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(buffer);
                    return NULL;
                }
                new_capacity = capacity * 2;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (ferror(stream) || (character == EOF && length == 0)) {
        free(buffer);
        return NULL;
    }

    if (length == SIZE_MAX) {
        free(buffer);
        return NULL;
    }

    if (length + 1 > capacity) {
        char *resized = realloc(buffer, length + 1);

        if (resized == NULL) {
            free(buffer);
            return NULL;
        }

        buffer = resized;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input;
    FloatTuple tuple;
    size_t i;

    input = read_line(stdin);
    if (input == NULL) {
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