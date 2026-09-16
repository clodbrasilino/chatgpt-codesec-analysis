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
    size_t i;

    if (tuple == NULL) {
        return;
    }

    for (i = 0; i < tuple->count; ++i) {
        free(tuple->items[i]);
    }

    free(tuple->items);
    tuple->items = NULL;
    tuple->count = 0;
}

static char *copy_trimmed_range(const char *begin, const char *end)
{
    size_t length;
    char *result;

    while (begin < end && isspace((unsigned char)*begin)) {
        ++begin;
    }

    while (end > begin && isspace((unsigned char)end[-1])) {
        --end;
    }

    length = (size_t)(end - begin);

    if (length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }

    if (length > 0) {
        memcpy(result, begin, length);
    }

    result[length] = '\0';
    return result;
}

static TupleStatus convert_string_to_tuple(const char *input, StringTuple *tuple)
{
    const char *begin;
    const char *end;
    const char *field_begin;
    const char *cursor;
    size_t field_count;
    size_t index;

    if (input == NULL || tuple == NULL) {
        return TUPLE_INVALID_ARGUMENT;
    }

    tuple->items = NULL;
    tuple->count = 0;

    begin = input;
    end = input + strlen(input);

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

    field_count = 1;

    for (cursor = begin; cursor < end; ++cursor) {
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
    field_begin = begin;
    index = 0;

    for (cursor = begin; cursor < end; ++cursor) {
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
    const unsigned char *cursor;

    if (value == NULL || putchar('"') == EOF) {
        return -1;
    }

    for (cursor = (const unsigned char *)value; *cursor != '\0'; ++cursor) {
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
    size_t i;

    if (tuple == NULL || putchar('(') == EOF) {
        return -1;
    }

    for (i = 0; i < tuple->count; ++i) {
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

    if (fputs(")\n", stdout) == EOF) {
        return -1;
    }

    return 0;
}

int main(int argc, char *const argv[])
{
    StringTuple tuple = { NULL, 0 };
    TupleStatus status;
    int result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"(value1, value2, value3)\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    status = convert_string_to_tuple(argv[1], &tuple);
    if (status != TUPLE_SUCCESS) {
        if (status == TUPLE_OUT_OF_MEMORY) {
            fputs("Unable to allocate memory.\n", stderr);
        } else {
            fputs("Invalid tuple string.\n", stderr);
        }

        return EXIT_FAILURE;
    }

    result = print_string_tuple(&tuple);
    free_string_tuple(&tuple);

    if (result != 0) {
        fputs("Unable to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}