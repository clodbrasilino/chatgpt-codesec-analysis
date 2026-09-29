#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static void free_string_list(char **list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0U; i < count; ++i) {
        free(list[i]);
    }

    free(list);
}

static int remove_duplicate_words(const char *const input[],
                                  const size_t input_lengths[],
                                  size_t input_count,
                                  char ***output,
                                  size_t *output_count)
{
    char **unique;
    size_t *unique_lengths;
    size_t unique_count = 0U;
    size_t i;

    if (output == NULL || output_count == NULL) {
        return -1;
    }

    *output = NULL;
    *output_count = 0U;

    if (input_count == 0U) {
        return 0;
    }

    if (input == NULL ||
        input_lengths == NULL ||
        input_count > SIZE_MAX / sizeof(*unique) ||
        input_count > SIZE_MAX / sizeof(*unique_lengths)) {
        return -1;
    }

    unique = calloc(input_count, sizeof(*unique));
    if (unique == NULL) {
        return -1;
    }

    unique_lengths = malloc(input_count * sizeof(*unique_lengths));
    if (unique_lengths == NULL) {
        free(unique);
        return -1;
    }

    for (i = 0U; i < input_count; ++i) {
        size_t j;
        int duplicate = 0;

        if (input[i] == NULL || input_lengths[i] == SIZE_MAX) {
            free(unique_lengths);
            free_string_list(unique, unique_count);
            return -1;
        }

        for (j = 0U; j < unique_count; ++j) {
            if (input_lengths[i] == unique_lengths[j] &&
                (input_lengths[i] == 0U ||
                 memcmp(input[i], unique[j], input_lengths[i]) == 0)) {
                duplicate = 1;
                break;
            }
        }

        if (!duplicate) {
            char *copy = duplicate_string(input[i], input_lengths[i]);

            if (copy == NULL) {
                free(unique_lengths);
                free_string_list(unique, unique_count);
                return -1;
            }

            unique[unique_count] = copy;
            unique_lengths[unique_count] = input_lengths[i];
            ++unique_count;
        }
    }

    free(unique_lengths);

    if (unique_count < input_count) {
        char **resized = realloc(unique, unique_count * sizeof(*unique));

        if (resized != NULL) {
            unique = resized;
        }
    }

    *output = unique;
    *output_count = unique_count;
    return 0;
}

int main(void)
{
    static const char word_0[] = "apple";
    static const char word_1[] = "banana";
    static const char word_2[] = "apple";
    static const char word_3[] = "orange";
    static const char word_4[] = "banana";
    static const char word_5[] = "grape";

    const char *const words[] = {
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

    char **unique_words = NULL;
    size_t unique_count = 0U;
    size_t i;

    if (remove_duplicate_words(words,
                               word_lengths,
                               sizeof(words) / sizeof(words[0]),
                               &unique_words,
                               &unique_count) != 0) {
        fputs("Failed to remove duplicate words.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < unique_count; ++i) {
        if (puts(unique_words[i]) == EOF) {
            free_string_list(unique_words, unique_count);
            return EXIT_FAILURE;
        }
    }

    free_string_list(unique_words, unique_count);
    return EXIT_SUCCESS;
}