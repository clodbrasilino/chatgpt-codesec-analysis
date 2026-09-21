#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void free_string_list(char **list, size_t count)
{
    if (list == NULL) {
        return;
    }

    for (size_t i = 0U; i < count; ++i) {
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
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    return copy;
}

static int remove_matching_words(const char *const input[],
                                 const size_t input_lengths[],
                                 size_t input_count,
                                 const char *pattern,
                                 size_t pattern_length,
                                 char ***output,
                                 size_t *output_count)
{
    char **result;
    size_t retained = 0U;

    if ((input_count != 0U &&
         (input == NULL || input_lengths == NULL)) ||
        pattern == NULL ||
        output == NULL ||
        output_count == NULL) {
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
        int matches = 0;

        if (input[i] == NULL) {
            free_string_list(result, retained);
            return -1;
        }

        if (pattern_length == 0U) {
            matches = 1;
        } else if (input_lengths[i] >= pattern_length) {
            size_t last = input_lengths[i] - pattern_length;

            for (size_t offset = 0U; offset <= last; ++offset) {
                if (memcmp(input[i] + offset,
                           pattern,
                           pattern_length) == 0) {
                    matches = 1;
                    break;
                }
            }
        }

        if (!matches) {
            result[retained] =
                duplicate_string(input[i], input_lengths[i]);

            if (result[retained] == NULL) {
                free_string_list(result, retained);
                return -1;
            }

            ++retained;
        }
    }

    if (retained == 0U) {
        free(result);
        result = NULL;
    } else {
        char **resized;

        if (retained > SIZE_MAX / sizeof(*result)) {
            free_string_list(result, retained);
            return -1;
        }

        resized = realloc(result, retained * sizeof(*result));
        if (resized != NULL) {
            result = resized;
        }
    }

    *output = result;
    *output_count = retained;

    return 0;
}

int main(void)
{
    static const char word_0[] = "apple";
    static const char word_1[] = "banana";
    static const char word_2[] = "grape";
    static const char word_3[] = "orange";
    static const char word_4[] = "pineapple";
    static const char word_5[] = "melon";
    static const char pattern[] = "apple";

    const char *words[] = {
        word_0,
        word_1,
        word_2,
        word_3,
        word_4,
        word_5
    };

    const size_t word_lengths[] = {
        sizeof(word_0) - 1U,
        sizeof(word_1) - 1U,
        sizeof(word_2) - 1U,
        sizeof(word_3) - 1U,
        sizeof(word_4) - 1U,
        sizeof(word_5) - 1U
    };

    char **filtered = NULL;
    size_t filtered_count = 0U;
    size_t word_count = sizeof(words) / sizeof(words[0]);

    if (remove_matching_words(words,
                              word_lengths,
                              word_count,
                              pattern,
                              sizeof(pattern) - 1U,
                              &filtered,
                              &filtered_count) != 0) {
        fputs("Failed to filter the string list.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < filtered_count; ++i) {
        if (puts(filtered[i]) == EOF) {
            free_string_list(filtered, filtered_count);
            return EXIT_FAILURE;
        }
    }

    free_string_list(filtered, filtered_count);
    return EXIT_SUCCESS;
}