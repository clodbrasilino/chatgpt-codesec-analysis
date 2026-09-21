#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;

static void tuple_destroy(Tuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    for (size_t i = 0; i < tuple->count; ++i) {
        free(tuple->items[i]);
    }

    free(tuple->items);
    tuple->items = NULL;
    tuple->count = 0;
}

static char *copy_trimmed(const char *begin, size_t length)
{
    if (begin == NULL) {
        errno = EINVAL;
        return NULL;
    }

    while (length > 0 &&
           (*begin == ' ' || *begin == '\t' ||
            *begin == '\n' || *begin == '\r')) {
        ++begin;
        --length;
    }

    while (length > 0 &&
           (begin[length - 1] == ' ' || begin[length - 1] == '\t' ||
            begin[length - 1] == '\n' || begin[length - 1] == '\r')) {
        --length;
    }

    if (length == SIZE_MAX) {
        errno = EOVERFLOW;
        return NULL;
    }

    char *result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        result[i] = begin[i];
    }

    result[length] = '\0';
    return result;
}

static int tuple_append(Tuple *tuple, char *item)
{
    if (tuple == NULL || item == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (tuple->count == SIZE_MAX ||
        tuple->count + 1 > SIZE_MAX / sizeof(*tuple->items)) {
        errno = EOVERFLOW;
        return -1;
    }

    size_t new_count = tuple->count + 1;
    char **new_items = realloc(
        tuple->items,
        new_count * sizeof(*tuple->items)
    );

    if (new_items == NULL) {
        return -1;
    }

    tuple->items = new_items;
    tuple->items[tuple->count] = item;
    tuple->count = new_count;
    return 0;
}

static int string_to_tuple_n(const char *input, size_t input_length, Tuple *tuple)
{
    if (input == NULL || tuple == NULL) {
        errno = EINVAL;
        return -1;
    }

    tuple->items = NULL;
    tuple->count = 0;

    size_t begin = 0;
    size_t end = input_length;

    if (input_length >= 2 && input[0] == '(' &&
        input[input_length - 1] == ')') {
        begin = 1;
        end = input_length - 1;
    }

    size_t field_begin = begin;

    for (size_t position = begin;; ++position) {
        if (position == end || input[position] == ',') {
            size_t field_length = position - field_begin;
            char *item = copy_trimmed(input + field_begin, field_length);

            if (item == NULL) {
                tuple_destroy(tuple);
                return -1;
            }

            if (tuple_append(tuple, item) != 0) {
                free(item);
                tuple_destroy(tuple);
                return -1;
            }

            if (position == end) {
                break;
            }

            field_begin = position + 1;
        }
    }

    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "tuple";

        fprintf(stderr, "Usage: %s \"(item1, item2, ...)\"\n", program);
        return EXIT_FAILURE;
    }

    size_t input_length = 0;
    while (argv[1][input_length] != '\0') {
        if (input_length == SIZE_MAX) {
            errno = EOVERFLOW;
            perror("input length");
            return EXIT_FAILURE;
        }
        ++input_length;
    }

    Tuple tuple = { NULL, 0 };

    if (string_to_tuple_n(argv[1], input_length, &tuple) != 0) {
        perror("string_to_tuple_n");
        return EXIT_FAILURE;
    }

    putchar('(');

    for (size_t i = 0; i < tuple.count; ++i) {
        if (i != 0) {
            fputs(", ", stdout);
        }

        putchar('"');
        fputs(tuple.items[i], stdout);
        putchar('"');
    }

    puts(")");
    tuple_destroy(&tuple);

    return EXIT_SUCCESS;
}