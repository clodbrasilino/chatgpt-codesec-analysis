#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    CHUNK_OK,
    CHUNK_INVALID_ARGUMENT,
    CHUNK_INCOMPLETE_TUPLE,
    CHUNK_SIZE_OVERFLOW,
    CHUNK_OUT_OF_MEMORY
} ChunkStatus;

typedef struct {
    int *data;
    size_t tuple_count;
    size_t tuple_size;
} TupleCollection;

static void tuple_collection_destroy(TupleCollection *collection)
{
    if (collection == NULL) {
        return;
    }

    free(collection->data);
    free(collection);
}

static TupleCollection *chunk_tuples(const int *values,
                                     size_t value_count,
                                     size_t tuple_size,
                                     ChunkStatus *status)
{
    TupleCollection *collection;
    size_t allocation_size;
    size_t i;

    if (status != NULL) {
        *status = CHUNK_INVALID_ARGUMENT;
    }

    if (tuple_size == 0 || (values == NULL && value_count != 0)) {
        return NULL;
    }

    if (value_count % tuple_size != 0) {
        if (status != NULL) {
            *status = CHUNK_INCOMPLETE_TUPLE;
        }
        return NULL;
    }

    if (value_count > SIZE_MAX / sizeof(*values)) {
        if (status != NULL) {
            *status = CHUNK_SIZE_OVERFLOW;
        }
        return NULL;
    }

    allocation_size = value_count * sizeof(*values);

    collection = calloc(1, sizeof(*collection));
    if (collection == NULL) {
        if (status != NULL) {
            *status = CHUNK_OUT_OF_MEMORY;
        }
        return NULL;
    }

    collection->tuple_count = value_count / tuple_size;
    collection->tuple_size = tuple_size;

    if (value_count != 0) {
        collection->data = malloc(allocation_size);
        if (collection->data == NULL) {
            tuple_collection_destroy(collection);
            if (status != NULL) {
                *status = CHUNK_OUT_OF_MEMORY;
            }
            return NULL;
        }

        for (i = 0; i < value_count; ++i) {
            collection->data[i] = values[i];
        }
    }

    if (status != NULL) {
        *status = CHUNK_OK;
    }

    return collection;
}

static const int *tuple_at(const TupleCollection *collection, size_t index)
{
    size_t offset;

    if (collection == NULL || index >= collection->tuple_count) {
        return NULL;
    }

    if (index > SIZE_MAX / collection->tuple_size) {
        return NULL;
    }

    offset = index * collection->tuple_size;
    return collection->data + offset;
}

static int parse_tuple_size(const char *text, size_t *value)
{
    const char *cursor;
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0') {
        return 0;
    }

    cursor = text;
    if (*cursor == '+') {
        ++cursor;
    }

    if (*cursor < '0' || *cursor > '9') {
        return 0;
    }

    while (*cursor >= '0' && *cursor <= '9') {
        ++cursor;
    }

    if (*cursor != '\0') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed == 0 || parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int parse_integer(const char *text, int *value)
{
    const char *cursor;
    char *end;
    intmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0') {
        return 0;
    }

    cursor = text;
    if (*cursor == '+' || *cursor == '-') {
        ++cursor;
    }

    if (*cursor < '0' || *cursor > '9') {
        return 0;
    }

    while (*cursor >= '0' && *cursor <= '9') {
        ++cursor;
    }

    if (*cursor != '\0') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return 0;
    }

    *value = (int)parsed;
    return 1;
}

static int print_tuples(const TupleCollection *collection)
{
    size_t i;
    size_t j;

    if (collection == NULL) {
        return 0;
    }

    for (i = 0; i < collection->tuple_count; ++i) {
        const int *tuple = tuple_at(collection, i);

        if (tuple == NULL || putchar('(') == EOF) {
            return 0;
        }

        for (j = 0; j < collection->tuple_size; ++j) {
            if (j != 0 && fputs(", ", stdout) == EOF) {
                return 0;
            }

            if (printf("%d", tuple[j]) < 0) {
                return 0;
            }
        }

        if (puts(")") == EOF) {
            return 0;
        }
    }

    return fflush(stdout) == 0;
}

int main(int argc, char **argv)
{
    TupleCollection *collection;
    ChunkStatus status;
    size_t tuple_size;
    size_t value_count;
    size_t allocation_size;
    int *values;
    int exit_code;
    size_t i;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s tuple_size [integers...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_tuple_size(argv[1], &tuple_size)) {
        fprintf(stderr, "Invalid tuple size\n");
        return EXIT_FAILURE;
    }

    value_count = (size_t)(argc - 2);

    if (value_count > SIZE_MAX / sizeof(*values)) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    allocation_size = value_count * sizeof(*values);
    values = NULL;

    if (value_count != 0) {
        values = malloc(allocation_size);
        if (values == NULL) {
            fprintf(stderr, "Unable to allocate input storage\n");
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < value_count; ++i) {
        if (!parse_integer(argv[i + 2], &values[i])) {
            fprintf(stderr, "Invalid integer: %s\n", argv[i + 2]);
            free(values);
            return EXIT_FAILURE;
        }
    }

    collection = chunk_tuples(values, value_count, tuple_size, &status);
    free(values);

    if (collection == NULL) {
        switch (status) {
            case CHUNK_INCOMPLETE_TUPLE:
                fprintf(stderr, "Input does not form complete tuples\n");
                break;
            case CHUNK_SIZE_OVERFLOW:
                fprintf(stderr, "Tuple storage size overflow\n");
                break;
            case CHUNK_OUT_OF_MEMORY:
                fprintf(stderr, "Unable to allocate tuple storage\n");
                break;
            case CHUNK_INVALID_ARGUMENT:
            default:
                fprintf(stderr, "Invalid chunking request\n");
                break;
        }

        return EXIT_FAILURE;
    }

    exit_code = print_tuples(collection) ? EXIT_SUCCESS : EXIT_FAILURE;

    if (exit_code != EXIT_SUCCESS) {
        fprintf(stderr, "Unable to write output\n");
    }

    tuple_collection_destroy(collection);
    return exit_code;
}