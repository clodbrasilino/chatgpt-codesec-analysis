#include <ctype.h>
#include <errno.h>
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
        tuple->size = 0U;
    }
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || capacity == NULL) {
        return 0;
    }

    if (required <= *capacity) {
        return 1;
    }

    new_capacity = (*capacity == 0U) ? 128U : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2U;
    }

    if (new_capacity < required) {
        return 0;
    }

    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return 0;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 1;
}

static char *read_line(FILE *stream)
{
    char *buffer = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int ch;

    if (stream == NULL) {
        return NULL;
    }

    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length > SIZE_MAX - 2U ||
            !grow_buffer(&buffer, &capacity, length + 2U)) {
            free(buffer);
            return NULL;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (ch == EOF && (ferror(stream) || length == 0U)) {
        free(buffer);
        return NULL;
    }

    if (!grow_buffer(&buffer, &capacity, length + 1U)) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

static int append_float(float **values, size_t *count, size_t *capacity,
                        float value)
{
    size_t new_capacity;
    float *new_values;

    if (values == NULL || count == NULL || capacity == NULL) {
        return 0;
    }

    if (*count < *capacity) {
        (*values)[*count] = value;
        ++(*count);
        return 1;
    }

    if (*count != *capacity) {
        return 0;
    }

    if (*capacity == 0U) {
        new_capacity = 4U;
    } else {
        if (*capacity > SIZE_MAX / 2U) {
            return 0;
        }
        new_capacity = *capacity * 2U;
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
    (*values)[*count] = value;
    ++(*count);
    return 1;
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

    while (isspace((unsigned char)*cursor) != 0) {
        ++cursor;
    }

    if (*cursor != '(') {
        return 0;
    }
    ++cursor;

    for (;;) {
        char *end;
        float value;

        while (isspace((unsigned char)*cursor) != 0) {
            ++cursor;
        }

        if (*cursor == ')') {
            ++cursor;
            break;
        }

        if (*cursor == '\0') {
            free(values);
            return 0;
        }

        errno = 0;
        value = strtof(cursor, &end);

        if (end == cursor || errno == ERANGE) {
            free(values);
            return 0;
        }

        cursor = end;

        if (!append_float(&values, &count, &capacity, value)) {
            free(values);
            return 0;
        }

        while (isspace((unsigned char)*cursor) != 0) {
            ++cursor;
        }

        if (*cursor == ',') {
            ++cursor;

            while (isspace((unsigned char)*cursor) != 0) {
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

    while (isspace((unsigned char)*cursor) != 0) {
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
    char *input;
    FloatTuple tuple = { NULL, 0U };
    size_t i;

    input = read_line(stdin);
    if (input == NULL) {
        fputs("Failed to read input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!string_to_float_tuple(input, &tuple)) {
        free(input);
        fputs("Invalid float tuple\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (putchar('(') == EOF) {
        free_float_tuple(&tuple);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < tuple.size; ++i) {
        if (i != 0U && fputs(", ", stdout) == EOF) {
            free_float_tuple(&tuple);
            return EXIT_FAILURE;
        }

        if (printf("%.9g", (double)tuple.values[i]) < 0) {
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