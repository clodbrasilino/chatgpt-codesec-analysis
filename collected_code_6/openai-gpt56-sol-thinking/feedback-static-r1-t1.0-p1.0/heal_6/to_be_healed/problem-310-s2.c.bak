#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} StringTuple;

typedef enum {
    TUPLE_SUCCESS,
    TUPLE_INVALID_ARGUMENT,
    TUPLE_INVALID_FORMAT,
    TUPLE_OUT_OF_MEMORY
} TupleStatus;

static void free_string_tuple(StringTuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    if (tuple->items != NULL) {
        for (size_t i = 0; i < tuple->count; ++i) {
            free(tuple->items[i]);
        }

        free(tuple->items);
    }

    tuple->items = NULL;
    tuple->count = 0;
}

static char *copy_trimmed_range(const char *begin, const char *end)
{
    while (begin < end && isspace((unsigned char)*begin)) {
        ++begin;
    }

    while (end > begin && isspace((unsigned char)end[-1])) {
        --end;
    }

    const size_t length = (size_t)(end - begin);

    if (length == SIZE_MAX) {
        return NULL;
    }

    char *result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }

    if (length != 0) {
        memcpy(result, begin, length);
    }

    result[length] = '\0';
    return result;
}

static TupleStatus convert_string_to_tuple(const char *input, StringTuple *tuple)
{
    if (input == NULL || tuple == NULL) {
        return TUPLE_INVALID_ARGUMENT;
    }

    tuple->items = NULL;
    tuple->count = 0;

    const char *begin = input;
    const char *end = input + strlen(input);

    while (begin < end && isspace((unsigned char)*begin)) {
        ++begin;
    }

    while (end > begin && isspace((unsigned char)end[-1])) {
        --end;
    }

    if (begin < end && *begin == '(') {
        if (end[-1] != ')') {
            return TUPLE_INVALID_FORMAT;
        }

        ++begin;
        --end;

        while (begin < end && isspace((unsigned char)*begin)) {
            ++begin;
        }

        while (end > begin && isspace((unsigned char)end[-1])) {
            --end;
        }
    } else if (begin < end && end[-1] == ')') {
        return TUPLE_INVALID_FORMAT;
    }

    if (begin == end) {
        return TUPLE_SUCCESS;
    }

    size_t field_count = 1;

    for (const char *cursor = begin; cursor < end; ++cursor) {
        if (*cursor == ',') {
            if (field_count == SIZE_MAX) {
                return TUPLE_OUT_OF_MEMORY;
            }

            ++field_count;
        }
    }

    if (field_count > SIZE_MAX / sizeof(*tuple->items)) {
        return TUPLE_OUT_OF_MEMORY;
    }

    tuple->items = calloc(field_count, sizeof(*tuple->items));
    if (tuple->items == NULL) {
        return TUPLE_OUT_OF_MEMORY;
    }

    tuple->count = field_count;

    const char *field_begin = begin;
    size_t index = 0;

    for (const char *cursor = begin; cursor < end; ++cursor) {
        if (*cursor != ',') {
            continue;
        }

        tuple->items[index] = copy_trimmed_range(field_begin, cursor);
        if (tuple->items[index] == NULL) {
            free_string_tuple(tuple);
            return TUPLE_OUT_OF_MEMORY;
        }

        ++index;
        field_begin = cursor + 1;
    }

    tuple->items[index] = copy_trimmed_range(field_begin, end);
    if (tuple->items[index] == NULL) {
        free_string_tuple(tuple);
        return TUPLE_OUT_OF_MEMORY;
    }

    return TUPLE_SUCCESS;
}

static int print_escaped_string(const char *value)
{
    if (value == NULL || putchar('"') == EOF) {
        return -1;
    }

    for (const unsigned char *cursor = (const unsigned char *)value;
         *cursor != '\0';
         ++cursor) {
        switch (*cursor) {
            case '"':
                if (fputs("\\\"", stdout) == EOF) {
                    return -1;
                }
                break;

            case '\\':
                if (fputs("\\\\", stdout) == EOF) {
                    return -1;
                }
                break;

            case '\n':
                if (fputs("\\n", stdout) == EOF) {
                    return -1;
                }
                break;

            case '\r':
                if (fputs("\\r", stdout) == EOF) {
                    return -1;
                }
                break;

            case '\t':
                if (fputs("\\t", stdout) == EOF) {
                    return -1;
                }
                break;

            default:
                if (isprint(*cursor)) {
                    if (putchar((int)*cursor) == EOF) {
                        return -1;
                    }
                } else if (printf("\\x%02X", (unsigned int)*cursor) < 0) {
                    return -1;
                }
                break;
        }
    }

    return putchar('"') == EOF ? -1 : 0;
}

static int print_string_tuple(const StringTuple *tuple)
{
    if (tuple == NULL || (tuple->count != 0 && tuple->items == NULL)) {
        return -1;
    }

    if (putchar('(') == EOF) {
        return -1;
    }

    for (size_t i = 0; i < tuple->count; ++i) {
        if (i != 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (print_escaped_string(tuple->items[i]) != 0) {
            return -1;
        }
    }

    if (tuple->count == 1 && putchar(',') == EOF) {
        return -1;
    }

    return fputs(")\n", stdout) == EOF ? -1 : 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[const])
{
    if (argc != 2) {
        fprintf(stderr,
                "Usage: %s \"(value1, value2, value3)\"\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    StringTuple tuple = {NULL, 0};
    const TupleStatus status = convert_string_to_tuple(argv[1], &tuple);

    if (status != TUPLE_SUCCESS) {
        switch (status) {
            case TUPLE_OUT_OF_MEMORY:
                fputs("Unable to allocate memory.\n", stderr);
                break;

            case TUPLE_INVALID_ARGUMENT:
                fputs("Invalid argument.\n", stderr);
                break;

            case TUPLE_INVALID_FORMAT:
                fputs("Invalid tuple string.\n", stderr);
                break;

            case TUPLE_SUCCESS:
                break;
        }

        return EXIT_FAILURE;
    }

    const int result = print_string_tuple(&tuple);
    free_string_tuple(&tuple);

    if (result != 0) {
        fputs("Unable to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}