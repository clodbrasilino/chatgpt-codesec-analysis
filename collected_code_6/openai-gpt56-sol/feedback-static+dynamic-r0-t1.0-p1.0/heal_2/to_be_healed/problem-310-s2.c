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

    if (length > SIZE_MAX - 1) {
        errno = EOVERFLOW;
        return NULL;
    }

    char *result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }

    if (length != 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result, begin, length);
    }

    result[length] = '\0';
    return result;
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
            if (tuple->count >= SIZE_MAX / sizeof(*tuple->items)) {
                tuple_destroy(tuple);
                errno = EOVERFLOW;
                return -1;
            }

            char *item = copy_trimmed(field_begin, p);
            if (item == NULL) {
                tuple_destroy(tuple);
                return -1;
            }

            size_t new_count = tuple->count + 1;
            char **new_items = realloc(
                tuple->items,
                new_count * sizeof(*tuple->items)
            );

            if (new_items == NULL) {
                free(item);
                tuple_destroy(tuple);
                return -1;
            }

            tuple->items = new_items;
            tuple->items[tuple->count] = item;
            tuple->count = new_count;

            if (p == end) {
                break;
            }

            field_begin = p + 1;
        }
    }

    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        const char *program = argc > 0 && argv[0] != NULL ? argv[0] : "tuple";
        fprintf(stderr, "Usage: %s \"(item1, item2, ...)\"\n", program);
        return EXIT_FAILURE;
    }

    Tuple tuple = { NULL, 0 };
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_length = strlen(argv[1]);

    if (string_to_tuple_n(argv[1], input_length, &tuple) != 0) {
        perror("string_to_tuple_n");
        return EXIT_FAILURE;
    }

    putchar('(');

    for (size_t i = 0; i < tuple.count; ++i) {
        if (i != 0) {
            fputs(", ", stdout);
        }

        printf("\"%s\"", tuple.items[i]);
    }

    puts(")");
    tuple_destroy(&tuple);

    return EXIT_SUCCESS;
}