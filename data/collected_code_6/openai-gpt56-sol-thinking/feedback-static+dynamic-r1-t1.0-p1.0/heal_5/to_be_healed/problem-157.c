#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    size_t count;
} Run;

static int run_length_encode(const int *input, size_t input_length,
                             Run **output, size_t *output_length)
{
    Run *runs;
    size_t run_count;
    size_t i;

    if (output == NULL || output_length == NULL) {
        return -1;
    }

    *output = NULL;
    *output_length = 0;

    if (input_length == 0) {
        return 0;
    }

    if (input == NULL || input_length > SIZE_MAX / sizeof(*runs)) {
        return -1;
    }

    runs = malloc(input_length * sizeof(*runs));
    if (runs == NULL) {
        return -1;
    }

    runs[0].value = input[0];
    runs[0].count = 1;
    run_count = 1;

    for (i = 1; i < input_length; ++i) {
        Run *current = &runs[run_count - 1];

        if (input[i] == current->value) {
            ++current->count;
        } else {
            runs[run_count].value = input[i];
            runs[run_count].count = 1;
            ++run_count;
        }
    }

    *output = runs;
    *output_length = run_count;

    return 0;
}

static int parse_integer(const char *text, int *value)
{
    char *end;
    long parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return -1;
    }

    errno = 0;
    parsed = strtol(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return -1;
    }

    *value = (int)parsed;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[])
{
    int *input = NULL;
    Run *encoded = NULL;
    size_t input_length;
    size_t encoded_length = 0;
    size_t i;
    int status = EXIT_FAILURE;

    input_length = argc > 1 ? (size_t)(argc - 1) : 0;

    if (input_length != 0) {
        if (input_length > SIZE_MAX / sizeof(*input)) {
            fputs("Input is too large.\n", stderr);
            return EXIT_FAILURE;
        }

        input = malloc(input_length * sizeof(*input));
        if (input == NULL) {
            fputs("Unable to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }

        for (i = 0; i < input_length; ++i) {
            if (parse_integer(argv[i + 1], &input[i]) != 0) {
                fprintf(stderr, "Invalid integer: %s\n", argv[i + 1]);
                goto cleanup;
            }
        }
    }

    if (run_length_encode(input, input_length, &encoded,
                          &encoded_length) != 0) {
        fputs("Unable to encode the input.\n", stderr);
        goto cleanup;
    }

    for (i = 0; i < encoded_length; ++i) {
        if (printf("%d %zu\n", encoded[i].value, encoded[i].count) < 0) {
            fputs("Unable to write output.\n", stderr);
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free(encoded);
    free(input);

    return status;
}