#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static int copy_string(const char *source, char **destination)
{
    size_t length;
    char *copy;

    if (source == NULL || destination == NULL) {
        return -1;
    }

    length = strlen(source);

    if (length == SIZE_MAX) {
        return -1;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return -1;
    }

    memcpy(copy, source, length + 1);
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
    const char *const values[],
    size_t value_count,
    size_t requested_length,
    char ***result,
    size_t *result_count)
{
    char **matches;
    size_t matches_count;

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

    matches_count = 0;

    for (size_t i = 0; i < value_count; ++i) {
        if (values[i] == NULL) {
            free_string_list(matches, matches_count);
            return -1;
        }

        if (strlen(values[i]) == requested_length) {
            if (copy_string(values[i], &matches[matches_count]) != 0) {
                free_string_list(matches, matches_count);
                return -1;
            }

            ++matches_count;
        }
    }

    if (matches_count == 0) {
        free(matches);
        return 0;
    }

    *result = matches;
    *result_count = matches_count;

    return 0;
}

int main(int argc, char *argv[])
{
    const char *program_name;
    const char **values;
    char **result;
    size_t requested_length;
    size_t value_count;
    size_t result_count;
    int status;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";
    values = NULL;
    result = NULL;
    result_count = 0;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s LENGTH [STRING ...]\n", program_name);
        return EXIT_FAILURE;
    }

    if (parse_size(argv[1], &requested_length) != 0) {
        fprintf(stderr, "Invalid string length: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    value_count = (size_t)(argc - 2);

    if (value_count != 0) {
        if (value_count > SIZE_MAX / sizeof(*values)) {
            fprintf(stderr, "Too many input strings\n");
            return EXIT_FAILURE;
        }

        values = malloc(value_count * sizeof(*values));
        if (values == NULL) {
            fprintf(stderr, "Failed to allocate input list\n");
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < value_count; ++i) {
            values[i] = argv[i + 2];
        }
    }

    status = extract_strings_by_length(
        values,
        value_count,
        requested_length,
        &result,
        &result_count
    );

    free(values);

    if (status != 0) {
        fprintf(stderr, "Failed to extract strings\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result_count; ++i) {
        puts(result[i]);
    }

    free_string_list(result, result_count);

    return EXIT_SUCCESS;
}