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

static char *copy_trimmed(const char *begin, const char *end)
{
    if (begin == NULL || end == NULL || end < begin) {
        errno = EINVAL;
        return NULL;
    }

    while (begin < end &&
           (*begin == ' ' || *begin == '\t' ||
            *begin == '\n' || *begin == '\r')) {
        ++begin;
    }

    while (end > begin &&
           (end[-1] == ' ' || end[-1] == '\t' ||
            end[-1] == '\n' || end[-1] == '\r')) {
        --end;
    }

    size_t length = (size_t)(end - begin);

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

    const char *begin = input;
    const char *end = input + input_length;

    if (input_length >= 2 && begin[0] == '(' && end[-1] == ')') {
        ++begin;
        --end;
    }

    const char *field_begin = begin;

    for (const char *p = begin;; ++p) {
        if (p == end || *p == ',') {
            char *item = copy_trimmed(field_begin, p);
            if (item == NULL) {
                tuple_destroy(tuple);
                return -1;
            }

            if (tuple_append(tuple, item) != 0) {
                free(item);
                tuple_destroy(tuple);
                return -1;
            }

            if (p == end) {
                break;
            }

            field_begin = p + 1;
        }
    }

    return 0;
}

static int write_quoted(const char *text)
{
    if (putchar('"') == EOF) {
        return -1;
    }

    for (const unsigned char *p = (const unsigned char *)text; *p != '\0'; ++p) {
        if (*p == '"' || *p == '\\') {
            if (putchar('\\') == EOF) {
                return -1;
            }
        }

        if (putchar(*p) == EOF) {
            return -1;
        }
    }

    return putchar('"') == EOF ? -1 : 0;
}

int main(int argc, char **argv)
{
    if (argc != 2 || argv == NULL || argv[0] == NULL || argv[1] == NULL) {
        const char *program = (argv != NULL && argv[0] != NULL)
                                  ? argv[0]
                                  : "tuple";
        fprintf(stderr, "Usage: %s \"(item1, item2, ...)\"\n", program);
        return EXIT_FAILURE;
    }

    size_t input_length = 0;
    while (argv[1][input_length] != '\0') {
        if (input_length == SIZE_MAX) {
            errno = EOVERFLOW;
            perror("input");
            return EXIT_FAILURE;
        }
        ++input_length;
    }

    Tuple tuple = { NULL, 0 };

    if (string_to_tuple_n(argv[1], input_length, &tuple) != 0) {
        perror("string_to_tuple_n");
        return EXIT_FAILURE;
    }

    int output_failed = putchar('(') == EOF;

    for (size_t i = 0; i < tuple.count && !output_failed; ++i) {
        if (i != 0 && fputs(", ", stdout) == EOF) {
            output_failed = 1;
            break;
        }

        if (write_quoted(tuple.items[i]) != 0) {
            output_failed = 1;
        }
    }

    if (!output_failed && puts(")") == EOF) {
        output_failed = 1;
    }

    tuple_destroy(&tuple);

    if (output_failed) {
        perror("output");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}