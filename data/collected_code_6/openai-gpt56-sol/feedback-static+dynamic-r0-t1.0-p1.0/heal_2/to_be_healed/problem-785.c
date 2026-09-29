#include <ctype.h>
#include <errno.h>
#include <stdint.h>
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

static int convert_tuple_string(const char *text, IntTuple *result)
{
    const char *p;
    int *values = NULL;
    size_t length = 0;
    size_t capacity = 0;

    if (text == NULL || result == NULL) {
        return -1;
    }

    result->values = NULL;
    result->length = 0;
    p = text;

    while (isspace((unsigned char)*p)) {
        ++p;
    }

    if (*p != '(') {
        return -1;
    }

    ++p;

    while (isspace((unsigned char)*p)) {
        ++p;
    }

    if (*p == ')') {
        ++p;

        while (isspace((unsigned char)*p)) {
            ++p;
        }

        return *p == '\0' ? 0 : -1;
    }

    for (;;) {
        char *end;
        long value;

        errno = 0;
        value = strtol(p, &end, 10);

        if (end == p || errno == ERANGE ||
            value < INT_MIN || value > INT_MAX) {
            free(values);
            return -1;
        }

        if (length == capacity) {
            size_t new_capacity;
            int *new_values;

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

            new_values = realloc(values, new_capacity * sizeof(*values));
            if (new_values == NULL) {
                free(values);
                return -1;
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
            return -1;
        }

        ++p;

        while (isspace((unsigned char)*p)) {
            ++p;
        }

        if (*p == '\0' || *p == ')' || *p == ',') {
            free(values);
            return -1;
        }
    }

    while (isspace((unsigned char)*p)) {
        ++p;
    }

    if (*p != '\0') {
        free(values);
        return -1;
    }

    result->values = values;
    result->length = length;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    IntTuple tuple = { NULL, 0 };
    size_t i;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"(1, 2, 3)\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (convert_tuple_string(argv[1], &tuple) != 0) {
        fputs("Invalid integer tuple\n", stderr);
        return EXIT_FAILURE;
    }

    putchar('(');

    for (i = 0; i < tuple.length; ++i) {
        if (i != 0) {
            fputs(", ", stdout);
        }
        printf("%d", tuple.values[i]);
    }

    puts(")");
    free_int_tuple(&tuple);

    return EXIT_SUCCESS;
}