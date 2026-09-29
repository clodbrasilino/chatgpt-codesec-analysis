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
    const char *const input[],
    size_t input_count,
    size_t requested_length,
    char ***output,
    size_t *output_count)
{
    char **result;
    size_t match_count = 0;
    size_t result_index = 0;
    size_t i;

    if (output == NULL || output_count == NULL) {
        return EINVAL;
    }

    *output = NULL;
    *output_count = 0;

    if (input_count != 0 && input == NULL) {
        return EINVAL;
    }

    for (i = 0; i < input_count; ++i) {
        if (input[i] == NULL) {
            return EINVAL;
        }

        if (strlen(input[i]) == requested_length) {
            ++match_count;
        }
    }

    if (match_count == 0) {
        return 0;
    }

    if (match_count > SIZE_MAX / sizeof(*result) ||
        requested_length == SIZE_MAX) {
        return ENOMEM;
    }

    result = calloc(match_count, sizeof(*result));
    if (result == NULL) {
        return ENOMEM;
    }

    for (i = 0; i < input_count; ++i) {
        if (strlen(input[i]) != requested_length) {
            continue;
        }

        result[result_index] = malloc(requested_length + 1);
        if (result[result_index] == NULL) {
            free_string_list(result, result_index);
            return ENOMEM;
        }

        memcpy(result[result_index], input[i], requested_length + 1);
        ++result_index;
    }

    *output = result;
    *output_count = result_index;

    return 0;
}

static int parse_size(const char *text, size_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL ||
        text[0] == '\0' || text[0] == '-') {
        return EINVAL;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text ||
        *end != '\0' || parsed > SIZE_MAX) {
        return ERANGE;
    }

    *value = (size_t)parsed;
    return 0;
}

static int run_program(int argc, char *const argv[])
{
    const char **input = NULL;
    char **matches = NULL;
    size_t input_count;
    size_t match_count = 0;
    size_t requested_length;
    size_t i;
    int status;
    int exit_status = EXIT_SUCCESS;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s LENGTH [STRING ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    status = parse_size(argv[1], &requested_length);
    if (status != 0) {
        fprintf(stderr, "Invalid length: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    input_count = (size_t)(argc - 2);

    if (input_count != 0) {
        if (input_count > SIZE_MAX / sizeof(*input)) {
            fprintf(stderr, "Input list is too large\n");
            return EXIT_FAILURE;
        }

        input = malloc(input_count * sizeof(*input));
        if (input == NULL) {
            fprintf(stderr, "Unable to allocate input list\n");
            return EXIT_FAILURE;
        }

        for (i = 0; i < input_count; ++i) {
            input[i] = argv[i + 2];
        }
    }

    status = extract_strings_by_length(
        input,
        input_count,
        requested_length,
        &matches,
        &match_count
    );

    free(input);

    if (status != 0) {
        fprintf(stderr, "Extraction failed: %s\n", strerror(status));
        return EXIT_FAILURE;
    }

    for (i = 0; i < match_count; ++i) {
        if (puts(matches[i]) == EOF) {
            exit_status = EXIT_FAILURE;
            break;
        }
    }

    free_string_list(matches, match_count);
    return exit_status;
}

int main(int argc, char *argv[])
{
    return run_program(argc, argv);
}