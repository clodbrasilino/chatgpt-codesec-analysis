#include <ctype.h>
#include <errno.h>
#include <limits.h>
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

        if (end == p || errno == ERANGE || value < INT_MIN || value > INT_MAX) {
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

        if (*p++ != ',') {
            free(values);
            return 0;
        }

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

int main(void)
{
    char input[4096];
    IntTuple tuple;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (parse_int_tuple(input, &tuple) == 0) {
        fputs("Invalid tuple\n", stderr);
        return EXIT_FAILURE;
    }

    putchar('(');
    for (size_t i = 0; i < tuple.length; ++i) {
        if (i != 0) {
            fputs(", ", stdout);
        }
        printf("%d", tuple.values[i]);
    }
    puts(")");

    free_int_tuple(&tuple);
    return EXIT_SUCCESS;
}