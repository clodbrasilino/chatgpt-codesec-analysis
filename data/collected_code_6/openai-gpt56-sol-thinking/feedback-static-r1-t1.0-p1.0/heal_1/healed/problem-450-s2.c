#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void free_string_list(char **strings, size_t count)
{
    size_t i;

    if (strings == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free(strings[i]);
    }

    free(strings);
}

static int measure_c_string(const char *string, size_t *length)
{
    size_t i;

    if (string == NULL || length == NULL) {
        return -1;
    }

    i = 0;

    for (;;) {
        if (string[i] == '\0') {
            *length = i;
            return 0;
        }

        if (i == SIZE_MAX) {
            return -1;
        }

        ++i;
    }
}

static int extract_strings_by_length(
    char *const *values,
    const size_t *value_lengths,
    size_t value_count,
    size_t required_length,
    char ***out_values,
    size_t *out_count)
{
    char **result;
    size_t match_count;
    size_t result_index;
    size_t i;
    size_t j;

    if (out_values == NULL || out_count == NULL ||
        (value_count != 0 && (values == NULL || value_lengths == NULL))) {
        return -1;
    }

    *out_values = NULL;
    *out_count = 0;
    match_count = 0;

    for (i = 0; i < value_count; ++i) {
        if (values[i] == NULL) {
            return -1;
        }

        if (value_lengths[i] == required_length) {
            ++match_count;
        }
    }

    if (match_count == 0) {
        return 0;
    }

    if (required_length == SIZE_MAX ||
        match_count > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    result = calloc(match_count, sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    result_index = 0;

    for (i = 0; i < value_count; ++i) {
        if (value_lengths[i] != required_length) {
            continue;
        }

        result[result_index] = malloc(required_length + 1);
        if (result[result_index] == NULL) {
            free_string_list(result, result_index);
            return -1;
        }

        for (j = 0; j < required_length; ++j) {
            result[result_index][j] = values[i][j];
        }

        result[result_index][required_length] = '\0';
        ++result_index;
    }

    *out_values = result;
    *out_count = result_index;
    return 0;
}

int main(int argc, char *argv[])
{
    char **matches;
    char *end;
    uintmax_t parsed_length;
    size_t *argument_lengths;
    size_t argument_count;
    size_t match_count;
    size_t required_length;
    size_t i;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <length> <string> [string ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '\0') {
        fprintf(stderr, "Invalid string length\n");
        return EXIT_FAILURE;
    }

    for (i = 0; argv[1][i] != '\0'; ++i) {
        if (argv[1][i] < '0' || argv[1][i] > '9') {
            fprintf(stderr, "Invalid string length\n");
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    end = NULL;
    parsed_length = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        parsed_length > SIZE_MAX) {
        fprintf(stderr, "Invalid string length\n");
        return EXIT_FAILURE;
    }

    required_length = (size_t)parsed_length;
    argument_count = (size_t)(argc - 2);

    if (argument_count > SIZE_MAX / sizeof(*argument_lengths)) {
        fprintf(stderr, "Unable to process arguments\n");
        return EXIT_FAILURE;
    }

    argument_lengths = calloc(argument_count, sizeof(*argument_lengths));
    if (argument_lengths == NULL) {
        fprintf(stderr, "Unable to process arguments\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < argument_count; ++i) {
        if (measure_c_string(argv[i + 2], &argument_lengths[i]) != 0) {
            free(argument_lengths);
            fprintf(stderr, "Unable to process arguments\n");
            return EXIT_FAILURE;
        }
    }

    if (extract_strings_by_length(
            argv + 2,
            argument_lengths,
            argument_count,
            required_length,
            &matches,
            &match_count) != 0) {
        free(argument_lengths);
        fprintf(stderr, "Unable to extract strings\n");
        return EXIT_FAILURE;
    }

    free(argument_lengths);

    for (i = 0; i < match_count; ++i) {
        puts(matches[i]);
    }

    free_string_list(matches, match_count);
    return EXIT_SUCCESS;
}