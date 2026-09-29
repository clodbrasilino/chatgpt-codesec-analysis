#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *data;
    size_t length;
} string_view;

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

static size_t argv_string_length(const char *value)
{
    size_t length = 0;

    while (value[length] != '\0') {
        ++length;
    }

    return length;
}

static int extract_strings_by_length(
    const string_view *values,
    size_t value_count,
    size_t required_length,
    char ***out_values,
    size_t *out_count)
{
    char **result;
    size_t match_count = 0;
    size_t result_index = 0;
    size_t i;
    size_t j;

    if (out_values == NULL || out_count == NULL) {
        return -1;
    }

    *out_values = NULL;
    *out_count = 0;

    if (values == NULL && value_count != 0) {
        return -1;
    }

    for (i = 0; i < value_count; ++i) {
        if (values[i].data == NULL) {
            return -1;
        }

        if (values[i].length == required_length) {
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

    for (i = 0; i < value_count; ++i) {
        if (values[i].length != required_length) {
            continue;
        }

        result[result_index] = malloc(required_length + 1);
        if (result[result_index] == NULL) {
            free_string_list(result, result_index);
            return -1;
        }

        for (j = 0; j < required_length; ++j) {
            result[result_index][j] = values[i].data[j];
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
    string_view *values;
    char **matches;
    char *end;
    const char *p;
    uintmax_t parsed_length;
    size_t value_count;
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

    for (p = argv[1]; *p != '\0'; ++p) {
        if (*p < '0' || *p > '9') {
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
    value_count = (size_t)(argc - 2);

    if (value_count > SIZE_MAX / sizeof(*values)) {
        fprintf(stderr, "Unable to prepare input strings\n");
        return EXIT_FAILURE;
    }

    values = malloc(value_count * sizeof(*values));
    if (values == NULL) {
        fprintf(stderr, "Unable to prepare input strings\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < value_count; ++i) {
        values[i].data = argv[i + 2];
        values[i].length = argv_string_length(argv[i + 2]);
    }

    if (extract_strings_by_length(
            values,
            value_count,
            required_length,
            &matches,
            &match_count) != 0) {
        free(values);
        fprintf(stderr, "Unable to extract strings\n");
        return EXIT_FAILURE;
    }

    free(values);

    for (i = 0; i < match_count; ++i) {
        puts(matches[i]);
    }

    free_string_list(matches, match_count);
    return EXIT_SUCCESS;
}