#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    size_t count;
} Run;

typedef enum {
    RLE_OK = 0,
    RLE_INVALID_ARGUMENT,
    RLE_SIZE_OVERFLOW,
    RLE_ALLOCATION_FAILURE
} RleStatus;

static RleStatus run_length_encode(const int *values, size_t length,
                                   Run **runs_out, size_t *run_count_out)
{
    Run *runs;
    size_t run_count;

    if (runs_out == NULL || run_count_out == NULL) {
        return RLE_INVALID_ARGUMENT;
    }

    *runs_out = NULL;
    *run_count_out = 0;

    if (length == 0) {
        return RLE_OK;
    }

    if (values == NULL) {
        return RLE_INVALID_ARGUMENT;
    }

    if (length > SIZE_MAX / sizeof(*runs)) {
        return RLE_SIZE_OVERFLOW;
    }

    runs = malloc(length * sizeof(*runs));
    if (runs == NULL) {
        return RLE_ALLOCATION_FAILURE;
    }

    runs[0].value = values[0];
    runs[0].count = 1;
    run_count = 1;

    for (size_t i = 1; i < length; ++i) {
        if (values[i] == runs[run_count - 1].value) {
            ++runs[run_count - 1].count;
        } else {
            runs[run_count].value = values[i];
            runs[run_count].count = 1;
            ++run_count;
        }
    }

    *runs_out = runs;
    *run_count_out = run_count;

    return RLE_OK;
}

static int parse_int(const char *text, int *value_out)
{
    char *end;
    long value;

    if (text == NULL || value_out == NULL || *text == '\0') {
        return 0;
    }

    errno = 0;
    value = strtol(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        value < INT_MIN || value > INT_MAX) {
        return 0;
    }

    *value_out = (int)value;

    return 1;
}

int main(int argc, char *const argv[])
{
    int *values = NULL;
    Run *runs = NULL;
    size_t value_count;
    size_t run_count = 0;
    RleStatus status;
    int result = EXIT_SUCCESS;

    if (argc < 1) {
        return EXIT_FAILURE;
    }

    value_count = (size_t)(argc - 1);

    if (value_count > SIZE_MAX / sizeof(*values)) {
        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    if (value_count != 0) {
        values = malloc(value_count * sizeof(*values));
        if (values == NULL) {
            fputs("Unable to allocate input storage.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < value_count; ++i) {
        if (!parse_int(argv[i + 1], &values[i])) {
            fprintf(stderr, "Invalid integer: %s\n", argv[i + 1]);
            free(values);
            return EXIT_FAILURE;
        }
    }

    status = run_length_encode(values, value_count, &runs, &run_count);
    free(values);

    if (status != RLE_OK) {
        fputs("Unable to encode the input.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < run_count; ++i) {
        if (printf("%d %zu\n", runs[i].value, runs[i].count) < 0) {
            result = EXIT_FAILURE;
            break;
        }
    }

    free(runs);

    if (fflush(stdout) == EOF) {
        result = EXIT_FAILURE;
    }

    return result;
}