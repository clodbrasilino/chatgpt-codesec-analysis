#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    size_t length;
} IntTuple;

static void free_int_tuple(IntTuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->values);
        tuple->values = NULL;
        tuple->length = 0;
    }
}

static int parse_int_tuple(const char *text, IntTuple *tuple)
{
    const char *p;
    int *values = NULL;
    size_t length = 0;
    size_t capacity = 0;

    if (text == NULL || tuple == NULL) {
        return 0;
    }

    tuple->values = NULL;
    tuple->length = 0;
    p = text;

    while (isspace((unsigned char)*p)) {
        ++p;
    }

    if (*p++ != '(') {
        return 0;
    }

    while (isspace((unsigned char)*p)) {
        ++p;
    }

    if (*p == ')') {
        ++p;
        while (isspace((unsigned char)*p)) {
            ++p;
        }
        return *p == '\0';
    }

    for (;;) {
        char *end;
        long value;

        errno = 0;
        value = strtol(p, &end, 10);

        if (end == p || errno == ERANGE ||
            value < INT_MIN || value > INT_MAX) {
            free(values);
            return 0;
        }

        if (length == capacity) {
            size_t new_capacity;
            int *new_values;

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

        values[length++] = (int)value;
        p = end;

        while (isspace((unsigned char)*p)) {
            ++p;
        }

        if (*p == ')') {
            ++p;
            break;
        }

        if (*p != ',') {
            free(values);
            return 0;
        }

        ++p;

        while (isspace((unsigned char)*p)) {
            ++p;
        }

        if (*p == ')' || *p == '\0') {
            free(values);
            return 0;
        }
    }

    while (isspace((unsigned char)*p)) {
        ++p;
    }

    if (*p != '\0') {
        free(values);
        return 0;
    }

    tuple->values = values;
    tuple->length = length;
    return 1;
}

static char *read_line(FILE *stream)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 128;

    if (stream == NULL || capacity > SIZE_MAX - 1) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        size_t available;

        if (length > capacity) {
            free(buffer);
            return NULL;
        }

        available = capacity - length;

        if (available < 2) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
            available = capacity - length;
        }

        if (fgets(buffer + length, (int)(available > INT_MAX
                                             ? INT_MAX
                                             : available),
                  stream) == NULL) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        while (buffer[length] != '\0' && buffer[length] != '\n') {
            ++length;
        }

        if (buffer[length] == '\n') {
            buffer[length] = '\0';
            return buffer;
        }

        if (feof(stream)) {
            break;
        }
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input;
    IntTuple tuple = {NULL, 0};

    input = read_line(stdin);
    if (input == NULL) {
        fputs("Failed to read input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!parse_int_tuple(input, &tuple)) {
        free(input);
        fputs("Invalid tuple\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (putchar('(') == EOF) {
        free_int_tuple(&tuple);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < tuple.length; ++i) {
        if ((i != 0 && fputs(", ", stdout) == EOF) ||
            printf("%d", tuple.values[i]) < 0) {
            free_int_tuple(&tuple);
            return EXIT_FAILURE;
        }
    }

    if (puts(")") == EOF) {
        free_int_tuple(&tuple);
        return EXIT_FAILURE;
    }

    free_int_tuple(&tuple);
    return EXIT_SUCCESS;
}