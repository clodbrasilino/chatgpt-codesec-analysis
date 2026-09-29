#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void free_string_list(char **list, size_t count)
{
    if (list == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(list[i]);
    }

    free(list);
}

static char *duplicate_string(const char *source, size_t length)
{
    char *copy;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static int remove_matching_strings(const char *const input[],
                                   const size_t input_lengths[],
                                   size_t input_count,
                                   const char *pattern,
                                   char ***output,
                                   size_t *output_count)
{
    char **result;
    size_t kept = 0U;

    if (input == NULL || input_lengths == NULL || pattern == NULL ||
        pattern[0] == '\0' || output == NULL || output_count == NULL) {
        return -1;
    }

    *output = NULL;
    *output_count = 0U;

    if (input_count == 0U) {
        return 0;
    }

    if (input_count > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    result = calloc(input_count, sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    for (size_t i = 0U; i < input_count; ++i) {
        if (input[i] == NULL) {
            free_string_list(result, kept);
            return -1;
        }

        if (strstr(input[i], pattern) == NULL) {
            result[kept] = duplicate_string(input[i], input_lengths[i]);
            if (result[kept] == NULL) {
                free_string_list(result, kept);
                return -1;
            }

            ++kept;
        }
    }

    if (kept == 0U) {
        free(result);
        result = NULL;
    } else {
        char **resized = realloc(result, kept * sizeof(*result));

        if (resized != NULL) {
            result = resized;
        }
    }

    *output = result;
    *output_count = kept;
    return 0;
}

int main(int argc, char *argv[])
{
    char **filtered = NULL;
    size_t *input_lengths = NULL;
    size_t filtered_count = 0U;
    size_t input_count;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <character-or-string> <word> [word ...]\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    if (argv[1] == NULL || argv[1][0] == '\0') {
        fputs("The pattern must not be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    input_count = (size_t)argc - 2U;

    if (input_count > SIZE_MAX / sizeof(*input_lengths)) {
        fputs("Input list is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    input_lengths = malloc(input_count * sizeof(*input_lengths));
    if (input_lengths == NULL) {
        fputs("Failed to allocate input metadata.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < input_count; ++i) {
        const char *argument = argv[i + 2U];

        if (argument == NULL) {
            free(input_lengths);
            fputs("Invalid input string.\n", stderr);
            return EXIT_FAILURE;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        input_lengths[i] = strlen(argument);
    }

    if (remove_matching_strings((const char *const *)&argv[2],
                                input_lengths,
                                input_count,
                                argv[1],
                                &filtered,
                                &filtered_count) != 0) {
        free(input_lengths);
        fputs("Failed to filter the string list.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input_lengths);

    for (size_t i = 0U; i < filtered_count; ++i) {
        if (puts(filtered[i]) == EOF) {
            free_string_list(filtered, filtered_count);
            return EXIT_FAILURE;
        }
    }

    free_string_list(filtered, filtered_count);
    return EXIT_SUCCESS;
}