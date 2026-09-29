#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    size_t count;
} IntTuple;

static void free_tuple(IntTuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->values);
        tuple->values = NULL;
        tuple->count = 0;
    }
}

static int parse_tuple(const char *input, IntTuple *tuple)
{
    const char *p;
    int *values = NULL;
    size_t count = 0;
    size_t capacity = 0;

    if (input == NULL || tuple == NULL) {
        return 0;
    }

    tuple->values = NULL;
    tuple->count = 0;
    p = input;

    for (;;) {
        char *end;
        long value;

        while (isspace((unsigned char)*p) || *p == ',') {
            ++p;
        }

        if (*p == '\0') {
            break;
        }

        errno = 0;
        value = strtol(p, &end, 10);

        if (end == p || errno == ERANGE ||
            value < INT_MIN || value > INT_MAX) {
            free(values);
            return 0;
        }

        if (*end != '\0' && *end != ',' &&
            !isspace((unsigned char)*end)) {
            free(values);
            return 0;
        }

        if (count == capacity) {
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

        values[count++] = (int)value;
        p = end;
    }

    if (count == 0) {
        free(values);
        return 0;
    }

    tuple->values = values;
    tuple->count = count;
    return 1;
}

static int print_tuple(const IntTuple *tuple)
{
    size_t i;

    if (tuple == NULL || tuple->values == NULL || tuple->count == 0) {
        return 0;
    }

    if (putchar('(') == EOF) {
        return 0;
    }

    for (i = 0; i < tuple->count; ++i) {
        if (i != 0 && fputs(", ", stdout) == EOF) {
            return 0;
        }

        if (printf("%d", tuple->values[i]) < 0) {
            return 0;
        }
    }

    if (tuple->count == 1 && putchar(',') == EOF) {
        return 0;
    }

    return fputs(")\n", stdout) != EOF;
}

int main(int argc, char *const argv[])
{
    IntTuple tuple = { NULL, 0 };
    int status;

    if (argc != 2) {
        const char *program = argc > 0 && argv[0] != NULL
                                ? argv[0]
                                : "program";

        fprintf(stderr, "Usage: %s \"integer string\"\n", program);
        return EXIT_FAILURE;
    }

    if (!parse_tuple(argv[1], &tuple)) {
        fputs("Invalid integer string\n", stderr);
        return EXIT_FAILURE;
    }

    status = print_tuple(&tuple) ? EXIT_SUCCESS : EXIT_FAILURE;
    free_tuple(&tuple);

    if (fflush(stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    return status;
}