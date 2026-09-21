#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *data;
    size_t length;
} string_view;

static int measure_string(const char *text, size_t *length)
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
    const string_view *values,
    size_t value_count,
    size_t requested_length,
    char ***result,
    size_t *result_count)
{
    char **matches;
    size_t match_capacity = 0;
    size_t matches_count = 0;

    if (result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if (value_count != 0 && values == NULL) {
        return -1;
    }

    for (size_t i = 0; i < value_count; ++i) {
        size_t actual_length;

        if (values[i].data == NULL ||
            measure_string(values[i].data, &actual_length) != 0 ||
            actual_length != values[i].length) {
            return -1;
        }

        if (actual_length == requested_length) {
            if (match_capacity == SIZE_MAX) {
                return -1;
            }
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

            if (argument == NULL ||
                measure_string(argument, &values[i].length) != 0) {
                fprintf(stderr, "Invalid input string\n");
                free(values);
                return EXIT_FAILURE;
            }

            values[i].data = argument;
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