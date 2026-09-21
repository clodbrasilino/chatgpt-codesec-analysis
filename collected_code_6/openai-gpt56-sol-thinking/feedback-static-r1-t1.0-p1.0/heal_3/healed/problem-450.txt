#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int parse_size(const char *text, size_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return -1;
    }

    for (const char *p = text; *p != '\0'; ++p) {
        if (*p < '0' || *p > '9') {
            return -1;
        }
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int get_string_length(const char *text, size_t *length)
{
    size_t count = 0;

    if (text == NULL || length == NULL) {
        return -1;
    }

    while (text[count] != '\0') {
        if (count == SIZE_MAX - 1) {
            return -1;
        }

        ++count;
    }

    *length = count;
    return 0;
}

static int copy_string(const char *source, size_t length, char **destination)
{
    char *copy;

    if (destination == NULL) {
        return -1;
    }

    *destination = NULL;

    if (source == NULL || length == SIZE_MAX) {
        return -1;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        copy[i] = source[i];
    }

    copy[length] = '\0';
    *destination = copy;
    return 0;
}

static void free_string_list(char **strings, size_t count)
{
    if (strings == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(strings[i]);
    }

    free(strings);
}

static int extract_strings_by_length(
    char *const *values,
    size_t value_count,
    size_t requested_length,
    char ***result,
    size_t *result_count)
{
    char **matches;
    size_t matches_count = 0;

    if (result == NULL || result_count == NULL ||
        (value_count != 0 && values == NULL)) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if (value_count == 0) {
        return 0;
    }

    if (value_count > SIZE_MAX / sizeof(*matches)) {
        return -1;
    }

    matches = calloc(value_count, sizeof(*matches));
    if (matches == NULL) {
        return -1;
    }

    for (size_t i = 0; i < value_count; ++i) {
        size_t length;

        if (get_string_length(values[i], &length) != 0) {
            free_string_list(matches, matches_count);
            return -1;
        }

        if (length != requested_length) {
            continue;
        }

        if (copy_string(values[i], length, &matches[matches_count]) != 0) {
            free_string_list(matches, matches_count);
            return -1;
        }

        ++matches_count;
    }

    if (matches_count == 0) {
        free(matches);
        return 0;
    }

    *result = matches;
    *result_count = matches_count;
    return 0;
}

int main(int argc, char **argv)
{
    const char *program_name;
    char *const *input_values;
    size_t requested_length;
    size_t value_count;
    size_t result_count;
    char **result;

    program_name =
        argc > 0 && argv != NULL && argv[0] != NULL && argv[0][0] != '\0'
            ? argv[0]
            : "program";

    if (argc < 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s LENGTH [STRING ...]\n", program_name);
        return EXIT_FAILURE;
    }

    if (parse_size(argv[1], &requested_length) != 0) {
        fprintf(stderr, "Invalid string length: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    value_count = (size_t)(argc - 2);
    input_values = value_count == 0 ? NULL : argv + 2;
    result = NULL;
    result_count = 0;

    if (extract_strings_by_length(
            input_values,
            value_count,
            requested_length,
            &result,
            &result_count) != 0) {
        fprintf(stderr, "Failed to extract strings\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result_count; ++i) {
        if (puts(result[i]) == EOF) {
            fprintf(stderr, "Failed to write output\n");
            free_string_list(result, result_count);
            return EXIT_FAILURE;
        }
    }

    free_string_list(result, result_count);
    return EXIT_SUCCESS;
}