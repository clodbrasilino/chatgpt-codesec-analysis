#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    unsigned char *items;
    size_t length;
} CharTuple;

CharTuple *string_to_tuple(const char *string)
{
    CharTuple *tuple;
    size_t length;

    if (string == NULL) {
        return NULL;
    }

    length = strlen(string);

    tuple = malloc(sizeof(*tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->items = NULL;
    tuple->length = length;

    if (length != 0) {
        tuple->items = malloc(length * sizeof(*tuple->items));
        if (tuple->items == NULL) {
            free(tuple);
            return NULL;
        }

        memcpy(tuple->items, string, length);
    }

    return tuple;
}

void free_tuple(CharTuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    free(tuple->items);
    free(tuple);
}

static int print_escaped_character(unsigned char value)
{
    switch (value) {
        case '\'':
            return fputs("\\'", stdout) == EOF ? -1 : 0;
        case '\\':
            return fputs("\\\\", stdout) == EOF ? -1 : 0;
        case '\n':
            return fputs("\\n", stdout) == EOF ? -1 : 0;
        case '\r':
            return fputs("\\r", stdout) == EOF ? -1 : 0;
        case '\t':
            return fputs("\\t", stdout) == EOF ? -1 : 0;
        case '\b':
            return fputs("\\b", stdout) == EOF ? -1 : 0;
        case '\f':
            return fputs("\\f", stdout) == EOF ? -1 : 0;
        case '\v':
            return fputs("\\v", stdout) == EOF ? -1 : 0;
        default:
            if (value >= 32 && value <= 126) {
                return fputc((int)value, stdout) == EOF ? -1 : 0;
            }

            return fprintf(stdout, "\\x%02X", (unsigned int)value) < 0
                       ? -1
                       : 0;
    }
}

int print_tuple(const CharTuple *tuple)
{
    size_t i;

    if (tuple == NULL ||
        (tuple->length != 0 && tuple->items == NULL)) {
        return -1;
    }

    if (fputc('[', stdout) == EOF) {
        return -1;
    }

    for (i = 0; i < tuple->length; ++i) {
        if (i != 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (fputc('\'', stdout) == EOF) {
            return -1;
        }

        if (print_escaped_character(tuple->items[i]) != 0) {
            return -1;
        }

        if (fputc('\'', stdout) == EOF) {
            return -1;
        }
    }

    if (fputs("]\n", stdout) == EOF) {
        return -1;
    }

    return fflush(stdout) == 0 ? 0 : -1;
}

int read_input_line(char **result)
{
    char *buffer;
    size_t length;
    size_t capacity;
    int ch;

    if (result == NULL) {
        return -1;
    }

    *result = NULL;
    length = 0;
    capacity = 64;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin)) {
        free(buffer);
        return -1;
    }

    if (length != 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *result = buffer;

    return 0;
}

int main(int argc, char **argv)
{
    const char *input;
    char *allocated_input;
    CharTuple *tuple;
    int status;

    allocated_input = NULL;

    if (argc == 2) {
        input = argv[1];
    } else if (argc == 1) {
        if (read_input_line(&allocated_input) != 0) {
            return EXIT_FAILURE;
        }

        input = allocated_input;
    } else {
        fprintf(stderr, "Usage: %s <string>\n",
                argv != NULL && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    tuple = string_to_tuple(input);
    free(allocated_input);

    if (tuple == NULL) {
        return EXIT_FAILURE;
    }

    status = print_tuple(tuple);
    free_tuple(tuple);

    return status == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}