#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *items;
    size_t size;
} IntTuple;

typedef struct {
    IntTuple *tuples;
    int *storage;
    size_t count;
} IntTupleCollection;

typedef enum {
    CHUNK_SUCCESS = 0,
    CHUNK_INVALID_ARGUMENT,
    CHUNK_INCOMPLETE_TUPLE,
    CHUNK_ALLOCATION_FAILURE
} ChunkStatus;

static void free_tuple_collection(IntTupleCollection *collection)
{
    if (collection == NULL) {
        return;
    }

    free(collection->storage);
    free(collection->tuples);

    collection->storage = NULL;
    collection->tuples = NULL;
    collection->count = 0;
}

static ChunkStatus chunk_into_tuples(
    const int *values,
    size_t value_count,
    size_t tuple_size,
    IntTupleCollection *result)
{
    size_t tuple_count;
    size_t i;

    if (result == NULL) {
        return CHUNK_INVALID_ARGUMENT;
    }

    result->tuples = NULL;
    result->storage = NULL;
    result->count = 0;

    if (tuple_size == 0 || (values == NULL && value_count != 0)) {
        return CHUNK_INVALID_ARGUMENT;
    }

    if (value_count % tuple_size != 0) {
        return CHUNK_INCOMPLETE_TUPLE;
    }

    if (value_count == 0) {
        return CHUNK_SUCCESS;
    }

    tuple_count = value_count / tuple_size;

    if (value_count > SIZE_MAX / sizeof(*result->storage) ||
        tuple_count > SIZE_MAX / sizeof(*result->tuples)) {
        return CHUNK_ALLOCATION_FAILURE;
    }

    result->storage = malloc(value_count * sizeof(*result->storage));
    if (result->storage == NULL) {
        return CHUNK_ALLOCATION_FAILURE;
    }

    result->tuples = malloc(tuple_count * sizeof(*result->tuples));
    if (result->tuples == NULL) {
        free_tuple_collection(result);
        return CHUNK_ALLOCATION_FAILURE;
    }

    memcpy(result->storage, values, value_count * sizeof(*values));

    for (i = 0; i < tuple_count; ++i) {
        result->tuples[i].items = result->storage + i * tuple_size;
        result->tuples[i].size = tuple_size;
    }

    result->count = tuple_count;
    return CHUNK_SUCCESS;
}

static int parse_size(const char *text, size_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        text[0] == '-' || text[0] == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int parse_int(const char *text, int *value)
{
    char *end;
    intmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return 0;
    }

    *value = (int)parsed;
    return 1;
}

int main(int argc, char *argv[const])
{
    IntTupleCollection collection = {0};
    ChunkStatus status;
    size_t tuple_size;
    size_t value_count;
    size_t i;
    size_t j;
    int *values = NULL;
    int exit_status = EXIT_FAILURE;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s tuple_size value [value ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_size(argv[1], &tuple_size) || tuple_size == 0) {
        fprintf(stderr, "Invalid tuple size: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    value_count = (size_t)(argc - 2);

    if (value_count > SIZE_MAX / sizeof(*values)) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    values = malloc(value_count * sizeof(*values));
    if (values == NULL) {
        fprintf(stderr, "Unable to allocate input storage\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < value_count; ++i) {
        if (!parse_int(argv[i + 2], &values[i])) {
            fprintf(stderr, "Invalid integer: %s\n", argv[i + 2]);
            goto cleanup;
        }
    }

    status = chunk_into_tuples(
        values,
        value_count,
        tuple_size,
        &collection
    );

    switch (status) {
    case CHUNK_SUCCESS:
        break;

    case CHUNK_INCOMPLETE_TUPLE:
        fprintf(
            stderr,
            "The number of values must be divisible by the tuple size\n"
        );
        goto cleanup;

    case CHUNK_ALLOCATION_FAILURE:
        fprintf(stderr, "Unable to allocate tuple storage\n");
        goto cleanup;

    case CHUNK_INVALID_ARGUMENT:
    default:
        fprintf(stderr, "Invalid chunking arguments\n");
        goto cleanup;
    }

    for (i = 0; i < collection.count; ++i) {
        putchar('(');

        for (j = 0; j < collection.tuples[i].size; ++j) {
            if (j != 0) {
                fputs(", ", stdout);
            }

            printf("%d", collection.tuples[i].items[j]);
        }

        puts(")");
    }

    if (ferror(stdout)) {
        fprintf(stderr, "Output error\n");
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    free_tuple_collection(&collection);
    free(values);

    return exit_status;
}