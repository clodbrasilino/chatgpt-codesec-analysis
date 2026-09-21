#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *data;
    size_t length;
} string_view;

static int parse_size(const char *text, size_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0') {
        return -1;
    }

    for (const unsigned char *p = (const unsigned char *)text;
         *p != '\0';
         ++p) {
        if (*p < (unsigned char)'0' || *p > (unsigned char)'9') {
            return -1;
        }
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || end == NULL || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int copy_string(const char *source, size_t length, char **destination)
{
    char *copy;

    if (source == NULL || destination == NULL || length == SIZE_MAX) {
        return -1;
    }

    *destination = NULL;

    copy = malloc(length + 1);
    if (copy == NULL) {
        return -1;
    }

    if (length != 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
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
    const string_view *values,
    size_t value_count,
    size_t requested_length,
    char ***result,
    size_t *result_count)
{
    char **matches;
    size_t match_capacity = 0;
    size_t matches_count = 0;

    if (result == NULL || result_count == NULL ||
        (value_count != 0 && values == NULL)) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    for (size_t i = 0; i < value_count; ++i) {
        if (values[i].data == NULL) {
            return -1;
        }

        if (values[i].length == requested_length) {
            ++match_capacity;
        }
    }

    if (match_capacity == 0) {
        return 0;
    }

    if (match_capacity > SIZE_MAX / sizeof(*matches)) {
        return -1;
    }

    matches = calloc(match_capacity, sizeof(*matches));
    if (matches == NULL) {
        return -1;
    }

    for (size_t i = 0; i < value_count; ++i) {
        if (values[i].length != requested_length) {
            continue;
        }

        if (copy_string(values[i].data,
                        values[i].length,
                        &matches[matches_count]) != 0) {
            free_string_list(matches, matches_count);
            return -1;
        }

        ++matches_count;
    }

    *result = matches;
    *result_count = matches_count;
    return 0;
}

int main(int argc, char **argv)
{
    const char *program_name = "program";
    size_t requested_length;
    size_t value_count;
    size_t result_count = 0;
    string_view *values = NULL;
    char **result = NULL;
    int status;

    if (argv != NULL && argc > 0 && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argv == NULL || argc < 2 || argv[1] == NULL) {
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

        values = calloc(value_count, sizeof(*values));
        if (values == NULL) {
            fprintf(stderr, "Failed to allocate input list\n");
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < value_count; ++i) {
            const char *argument = argv[i + 2];

            if (argument == NULL) {
                fprintf(stderr, "Invalid input string\n");
                free(values);
                return EXIT_FAILURE;
            }

            values[i].data = argument;
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            values[i].length = strlen(argument);
        }
    }

    status = extract_strings_by_length(
        values,
        value_count,
        requested_length,
        &result,
        &result_count);

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