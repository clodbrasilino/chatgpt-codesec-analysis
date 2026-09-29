#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    size_t size;
} IntTuple;

static void free_tuple(IntTuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->values);
        tuple->values = NULL;
        tuple->size = 0;
    }
}

static int is_separator(char character)
{
    return character == ',' || character == ' ' || character == '\t' ||
           character == '\n' || character == '\r' || character == '\f' ||
           character == '\v';
}

static int parse_tuple(const char *input, IntTuple *tuple)
{
    const char *cursor;
    int *values = NULL;
    size_t size = 0;
    size_t capacity = 0;

    if (input == NULL || tuple == NULL) {
        return 0;
    }

    tuple->values = NULL;
    tuple->size = 0;
    cursor = input;

    while (*cursor != '\0') {
        char *end;
        long value;

        while (is_separator(*cursor)) {
            ++cursor;
        }

        if (*cursor == '\0') {
            break;
        }

        errno = 0;
        value = strtol(cursor, &end, 10);

        if (end == cursor || errno == ERANGE ||
            value < INT_MIN || value > INT_MAX) {
            free(values);
            return 0;
        }

        if (*end != '\0' && !is_separator(*end)) {
            free(values);
            return 0;
        }

        if (size == capacity) {
            size_t new_capacity;
            int *new_values;

            if (capacity == 0) {
                new_capacity = 8;
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

        values[size++] = (int)value;
        cursor = end;
    }

    tuple->values = values;
    tuple->size = size;
    return 1;
}

static int print_tuple(const IntTuple *tuple)
{
    size_t i;

    if (putchar('(') == EOF) {
        return 0;
    }

    for (i = 0; i < tuple->size; ++i) {
        if (i != 0 && fputs(", ", stdout) == EOF) {
            return 0;
        }

        if (printf("%d", tuple->values[i]) < 0) {
            return 0;
        }
    }

    if (tuple->size == 1 && putchar(',') == EOF) {
        return 0;
    }

    return puts(")") != EOF;
}

int main(int argc, char *const argv[])
{
    IntTuple tuple = { NULL, 0 };
    int printed;

    if (argc != 2) {
        const char *program = argc > 0 && argv[0] != NULL ? argv[0] : "program";
        fprintf(stderr, "Usage: %s \"integer list\"\n", program);
        return EXIT_FAILURE;
    }

    if (!parse_tuple(argv[1], &tuple)) {
        fputs("Invalid integer list or memory allocation failure\n", stderr);
        return EXIT_FAILURE;
    }

    printed = print_tuple(&tuple);
    free_tuple(&tuple);

    if (!printed || ferror(stdout)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}