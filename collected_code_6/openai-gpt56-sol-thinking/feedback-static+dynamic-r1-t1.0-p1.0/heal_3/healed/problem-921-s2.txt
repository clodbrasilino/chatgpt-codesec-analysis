#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t tuple_count;
    size_t tuple_size;
} TupleCollection;

static void free_tuple_collection(TupleCollection *collection)
{
    if (collection == NULL) {
        return;
    }

    free(collection->data);
    collection->data = NULL;
    collection->tuple_count = 0;
    collection->tuple_size = 0;
}

static int chunk_into_tuples(const int *values, size_t value_count,
                             size_t tuple_size, TupleCollection *result)
{
    int *data = NULL;

    if (result == NULL || tuple_size == 0 ||
        (value_count != 0 && values == NULL) ||
        value_count % tuple_size != 0) {
        return -1;
    }

    result->data = NULL;
    result->tuple_count = 0;
    result->tuple_size = 0;

    if (value_count > SIZE_MAX / sizeof(*data)) {
        return -1;
    }

    if (value_count != 0) {
        data = malloc(value_count * sizeof(*data));
        if (data == NULL) {
            return -1;
        }

        for (size_t i = 0; i < value_count; ++i) {
            data[i] = values[i];
        }
    }

    result->data = data;
    result->tuple_count = value_count / tuple_size;
    result->tuple_size = tuple_size;

    return 0;
}

static int parse_size(const char *text, size_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return -1;
    }

    for (const char *cursor = text; *cursor != '\0'; ++cursor) {
        if (*cursor < '0' || *cursor > '9') {
            return -1;
        }
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed == 0 || parsed > SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int parse_int(const char *text, int *value)
{
    const char *cursor;
    char *end = NULL;
    intmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return -1;
    }

    cursor = text;

    if (*cursor == '+' || *cursor == '-') {
        ++cursor;
    }

    if (*cursor == '\0') {
        return -1;
    }

    for (; *cursor != '\0'; ++cursor) {
        if (*cursor < '0' || *cursor > '9') {
            return -1;
        }
    }

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return -1;
    }

    *value = (int)parsed;
    return 0;
}

int main(int argc, char *argv[const])
{
    TupleCollection tuples = {0};
    size_t tuple_size;
    size_t value_count;
    int *values = NULL;
    int status = EXIT_FAILURE;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s tuple_size value...\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_size(argv[1], &tuple_size) != 0) {
        fprintf(stderr, "Invalid tuple size\n");
        return EXIT_FAILURE;
    }

    value_count = (size_t)argc - 2;

    if (value_count % tuple_size != 0) {
        fprintf(stderr,
                "The number of values must be divisible by the tuple size\n");
        return EXIT_FAILURE;
    }

    if (value_count > SIZE_MAX / sizeof(*values)) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    values = malloc(value_count * sizeof(*values));
    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < value_count; ++i) {
        if (parse_int(argv[i + 2], &values[i]) != 0) {
            fprintf(stderr, "Invalid integer: %s\n", argv[i + 2]);
            goto cleanup;
        }
    }

    if (chunk_into_tuples(values, value_count, tuple_size, &tuples) != 0) {
        fprintf(stderr, "Unable to create tuples\n");
        goto cleanup;
    }

    for (size_t i = 0; i < tuples.tuple_count; ++i) {
        putchar('(');

        for (size_t j = 0; j < tuples.tuple_size; ++j) {
            if (j != 0) {
                fputs(", ", stdout);
            }

            printf("%d", tuples.data[i * tuples.tuple_size + j]);
        }

        puts(")");
    }

    if (ferror(stdout)) {
        fprintf(stderr, "Output error\n");
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free_tuple_collection(&tuples);
    free(values);
    return status;
}