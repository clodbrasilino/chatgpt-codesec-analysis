#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static int extract_strings_by_length(
    const char *const *values,
    size_t value_count,
    size_t required_length,
    char ***out_values,
    size_t *out_count)
{
    char **result;
    size_t match_count;
    size_t result_index;
    size_t i;

    if (out_values == NULL || out_count == NULL ||
        (values == NULL && value_count != 0)) {
        return -1;
    }

    *out_values = NULL;
    *out_count = 0;
    match_count = 0;

    for (i = 0; i < value_count; ++i) {
        if (values[i] == NULL) {
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(values[i]) == required_length) {
            ++match_count;
        }
    }

    if (match_count == 0) {
        return 0;
    }

    if (match_count > SIZE_MAX / sizeof(*result) ||
        required_length == SIZE_MAX) {
        return -1;
    }

    result = calloc(match_count, sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    result_index = 0;

    for (i = 0; i < value_count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(values[i]) != required_length) {
            continue;
        }

        result[result_index] = malloc(required_length + 1);
        if (result[result_index] == NULL) {
            free_string_list(result, result_index);
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[result_index], values[i], required_length + 1);
        ++result_index;
    }

    *out_values = result;
    *out_count = match_count;
    return 0;
}

int main(int argc, char *argv[])
{
    char **matches;
    char *end;
    uintmax_t parsed_length;
    size_t match_count;
    size_t required_length;
    size_t i;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <length> <string> [string ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '\0' || argv[1][0] == '-') {
        fprintf(stderr, "Invalid string length\n");
        return EXIT_FAILURE;
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

    if (extract_strings_by_length(
            (const char *const *)&argv[2],
            (size_t)(argc - 2),
            required_length,
            &matches,
            &match_count) != 0) {
        fprintf(stderr, "Unable to extract strings\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < match_count; ++i) {
        puts(matches[i]);
    }

    free_string_list(matches, match_count);
    return EXIT_SUCCESS;
}