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
    char *copy;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0) {
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static int contains_pattern(const char *string, size_t string_length,
                            const char *pattern, size_t pattern_length)
{
    size_t last;

    if (pattern_length > string_length) {
        return 0;
    }

    last = string_length - pattern_length;

    for (size_t i = 0; i <= last; ++i) {
        if (memcmp(string + i, pattern, pattern_length) == 0) {
            return 1;
        }
    }

    return 0;
}

static int remove_matching_strings(const char *const input[],
                                   size_t input_count,
                                   const char *pattern,
                                   size_t pattern_length,
                                   char ***output,
                                   size_t *output_count)
{
    char **result;
    size_t kept = 0;

    if (output == NULL || output_count == NULL) {
        return -1;
    }

    *output = NULL;
    *output_count = 0;

    if (input == NULL || pattern == NULL || pattern_length == 0) {
        return -1;
    }

    if (input_count == 0) {
        return 0;
    }

    if (input_count > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    result = calloc(input_count, sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < input_count; ++i) {
        size_t input_length;

        if (input[i] == NULL) {
            free_string_list(result, kept);
            return -1;
        }

        input_length = strnlen(input[i], SIZE_MAX);
        if (input_length == SIZE_MAX) {
            free_string_list(result, kept);
            return -1;
        }

        if (!contains_pattern(input[i], input_length,
                              pattern, pattern_length)) {
            result[kept] = duplicate_string(input[i], input_length);
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
    char **filtered = NULL;
    size_t filtered_count = 0;
    size_t input_count;
    size_t pattern_length;

    if (argc < 3 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <character-or-string> <word> [word ...]\n",
                argc > 0 && argv != NULL && argv[0] != NULL
                    ? argv[0]
                    : "program");
        return EXIT_FAILURE;
    }

    pattern_length = strnlen(argv[1], SIZE_MAX);
    if (pattern_length == 0 || pattern_length == SIZE_MAX) {
        fputs("The search pattern must not be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    input_count = (size_t)(argc - 2);

    if (remove_matching_strings(
            (const char *const *)(argv + 2),
            input_count,
            argv[1],
            pattern_length,
            &filtered,
            &filtered_count) != 0) {
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