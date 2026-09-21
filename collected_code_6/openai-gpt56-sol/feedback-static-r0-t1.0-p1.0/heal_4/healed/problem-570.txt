#define _POSIX_C_SOURCE 200809L

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
    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    char *copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length);
    copy[length] = '\0';

    return copy;
}

static int contains_pattern(const char *string, size_t string_length,
                            const char *pattern, size_t pattern_length)
{
    if (string == NULL || pattern == NULL || pattern_length == 0 ||
        pattern_length > string_length) {
        return 0;
    }

    for (size_t i = 0; i <= string_length - pattern_length; ++i) {
        if (memcmp(string + i, pattern, pattern_length) == 0) {
            return 1;
        }
    }

    return 0;
}

static int remove_matching_strings(const char *const input[],
                                   const size_t input_lengths[],
                                   size_t input_count,
                                   const char *pattern,
                                   size_t pattern_length,
                                   char ***output,
                                   size_t *output_count)
{
    if (output == NULL || output_count == NULL) {
        return -1;
    }

    *output = NULL;
    *output_count = 0;

    if (pattern == NULL || pattern_length == 0 ||
        (input_count != 0 && (input == NULL || input_lengths == NULL))) {
        return -1;
    }

    if (input_count == 0) {
        return 0;
    }

    if (input_count > SIZE_MAX / sizeof(char *)) {
        return -1;
    }

    char **result = calloc(input_count, sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    size_t kept = 0;

    for (size_t i = 0; i < input_count; ++i) {
        if (input[i] == NULL || input_lengths[i] == SIZE_MAX) {
            free_string_list(result, kept);
            return -1;
        }

        if (!contains_pattern(input[i], input_lengths[i],
                              pattern, pattern_length)) {
            result[kept] = duplicate_string(input[i], input_lengths[i]);
            if (result[kept] == NULL) {
                free_string_list(result, kept);
                return -1;
            }

            ++kept;
        }
    }

    if (kept == 0) {
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
    if (argc < 3 || argv == NULL || argv[0] == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <character-or-string> <word> [word ...]\n",
                argv != NULL && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    size_t pattern_length = strnlen(argv[1], SIZE_MAX);
    if (pattern_length == 0) {
        fputs("The search pattern must not be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    size_t input_count = (size_t)(argc - 2);

    if (input_count > SIZE_MAX / sizeof(size_t)) {
        fputs("Too many input strings.\n", stderr);
        return EXIT_FAILURE;
    }

    size_t *input_lengths = malloc(input_count * sizeof(*input_lengths));
    if (input_lengths == NULL) {
        fputs("Failed to allocate input lengths.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < input_count; ++i) {
        if (argv[i + 2] == NULL) {
            free(input_lengths);
            fputs("Invalid input string.\n", stderr);
            return EXIT_FAILURE;
        }

        input_lengths[i] = strnlen(argv[i + 2], SIZE_MAX);
    }

    char **filtered = NULL;
    size_t filtered_count = 0;

    int status = remove_matching_strings(
        (const char *const *)(argv + 2),
        input_lengths,
        input_count,
        argv[1],
        pattern_length,
        &filtered,
        &filtered_count);

    free(input_lengths);

    if (status != 0) {
        fputs("Failed to filter the string list.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < filtered_count; ++i) {
        if (puts(filtered[i]) == EOF) {
            free_string_list(filtered, filtered_count);
            return EXIT_FAILURE;
        }
    }

    free_string_list(filtered, filtered_count);

    return EXIT_SUCCESS;
}