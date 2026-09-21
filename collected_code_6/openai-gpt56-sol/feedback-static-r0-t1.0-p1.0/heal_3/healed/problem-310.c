#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} StringTuple;

static void free_tuple(StringTuple *tuple)
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

static char *duplicate_range(const char *start, size_t length)
{
    char *copy;

    if (start == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0) {
        memcpy(copy, start, length);
    }

    copy[length] = '\0';
    return copy;
}

static int string_to_tuple_n(const char *input, size_t input_length,
                             char delimiter, StringTuple *tuple)
{
    size_t count = 1;
    size_t index = 0;
    size_t start = 0;
    size_t position;
    char **items;

    if (input == NULL || tuple == NULL || delimiter == '\0') {
        return -1;
    }

    tuple->items = NULL;
    tuple->count = 0;

    for (position = 0; position < input_length; ++position) {
        if (input[position] == '\0') {
            return -1;
        }

        if (input[position] == delimiter) {
            if (count == SIZE_MAX) {
                return -1;
            }
            ++count;
        }
    }

    if (count > SIZE_MAX / sizeof(*items)) {
        return -1;
    }

    items = calloc(count, sizeof(*items));
    if (items == NULL) {
        return -1;
    }

    for (position = 0; position <= input_length; ++position) {
        if (position == input_length || input[position] == delimiter) {
            size_t length = position - start;

            items[index] = duplicate_range(input + start, length);
            if (items[index] == NULL) {
                StringTuple partial = {items, index};
                free_tuple(&partial);
                return -1;
            }

            ++index;
            start = position + 1;
        }
    }

    tuple->items = items;
    tuple->count = index;
    return 0;
}

static void print_quoted_string(const char *string)
{
    const unsigned char *current;

    if (string == NULL) {
        fputs("\"\"", stdout);
        return;
    }

    current = (const unsigned char *)string;
    putchar('"');

    while (*current != '\0') {
        switch (*current) {
        case '\\':
            fputs("\\\\", stdout);
            break;
        case '"':
            fputs("\\\"", stdout);
            break;
        case '\n':
            fputs("\\n", stdout);
            break;
        case '\r':
            fputs("\\r", stdout);
            break;
        case '\t':
            fputs("\\t", stdout);
            break;
        default:
            if (*current < 0x20 || *current == 0x7f) {
                fprintf(stdout, "\\x%02X", (unsigned int)*current);
            } else {
                putchar((int)*current);
            }
            break;
        }

        ++current;
    }

    putchar('"');
}

static void print_tuple(const StringTuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        return;
    }

    putchar('(');

    for (i = 0; i < tuple->count; ++i) {
        if (i != 0) {
            fputs(", ", stdout);
        }

        print_quoted_string(tuple->items[i]);
    }

    if (tuple->count == 1) {
        putchar(',');
    }

    puts(")");
}

int main(int argc, char *argv[])
{
    StringTuple tuple = {NULL, 0};
    size_t input_length;

    if (argc != 3 || argv == NULL || argv[0] == NULL ||
        argv[1] == NULL || argv[2] == NULL ||
        argv[2][0] == '\0' || argv[2][1] != '\0') {
        fprintf(stderr, "Usage: %s <string> <delimiter>\n",
                argv != NULL && argc > 0 && argv[0] != NULL
                    ? argv[0]
                    : "program");
        return EXIT_FAILURE;
    }

    input_length = strlen(argv[1]);

    if (string_to_tuple_n(argv[1], input_length, argv[2][0], &tuple) != 0) {
        fputs("Failed to convert string to tuple.\n", stderr);
        return EXIT_FAILURE;
    }

    print_tuple(&tuple);
    free_tuple(&tuple);

    if (ferror(stdout)) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}