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

    memcpy(copy, source, length);
    copy[length] = '\0';

    return copy;
}

static int remove_matching_strings(const char *const input[],
                                   const size_t input_lengths[],
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

    if (pattern == NULL || pattern_length == 0) {
        return -1;
    }

    if (input_count == 0) {
        return 0;
    }

    if (input == NULL || input_lengths == NULL ||
        input_count > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    result = calloc(input_count, sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < input_count; ++i) {
        int matches = 0;

        if (input[i] == NULL) {
            free_string_list(result, kept);
            return -1;
        }

        if (pattern_length <= input_lengths[i]) {
            size_t last = input_lengths[i] - pattern_length;

            for (size_t offset = 0; offset <= last; ++offset) {
                if (memcmp(input[i] + offset, pattern, pattern_length) == 0) {
                    matches = 1;
                    break;
                }
            }
        }

        if (matches) {
            continue;
        }

        result[kept] = duplicate_string(input[i], input_lengths[i]);
        if (result[kept] == NULL) {
            free_string_list(result, kept);
            return -1;
        }

        ++kept;
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
    size_t *input_lengths;

    if (argc < 3) {
        fprintf(stderr,
                "Usage: %s <character-or-string> <word> [word ...]\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    if (argv[1] == NULL) {
        fputs("The pattern must not be null.\n", stderr);
        return EXIT_FAILURE;
    }

    pattern_length = strlen(argv[1]);
    if (pattern_length == 0) {
        fputs("The pattern must not be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    input_count = (size_t)(argc - 2);

    if (input_count > SIZE_MAX / sizeof(*input_lengths)) {
        fputs("Too many input strings.\n", stderr);
        return EXIT_FAILURE;
    }

    input_lengths = malloc(input_count * sizeof(*input_lengths));
    if (input_lengths == NULL) {
        fputs("Failed to allocate input length storage.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < input_count; ++i) {
        if (argv[i + 2] == NULL) {
            free(input_lengths);
            fputs("Invalid input string.\n", stderr);
            return EXIT_FAILURE;
        }

        input_lengths[i] = strlen(argv[i + 2]);
    }

    if (remove_matching_strings((const char *const *)(argv + 2),
                                input_lengths,
                                input_count,
                                argv[1],
                                pattern_length,
                                &filtered,
                                &filtered_count) != 0) {
        free(input_lengths);
        fputs("Failed to filter the string list.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input_lengths);

    for (size_t i = 0; i < filtered_count; ++i) {
        if (puts(filtered[i]) == EOF) {
            free_string_list(filtered, filtered_count);
            return EXIT_FAILURE;
        }
    }

    free_string_list(filtered, filtered_count);

    return EXIT_SUCCESS;
}