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
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    return copy;
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

    if (output == NULL || output_count == NULL ||
        (input_count != 0U && (input == NULL || input_lengths == NULL))) {
        return -1;
    }

    *output = NULL;
    *output_count = 0U;

    if (input_count == 0U) {
        return 0;
    }

    if (input_count > SIZE_MAX / sizeof(*unique) ||
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

    for (size_t i = 0U; i < input_count; ++i) {
        int found = 0;

        if (input[i] == NULL || input_lengths[i] == SIZE_MAX) {
            free(unique_lengths);
            free_string_list(unique, unique_count);
            return -1;
        }

        for (size_t j = 0U; j < unique_count; ++j) {
            if (input_lengths[i] == unique_lengths[j] &&
                (input_lengths[i] == 0U ||
                 memcmp(input[i], unique[j], input_lengths[i]) == 0)) {
                found = 1;
                break;
            }
        }

        if (!found) {
            unique[unique_count] =
                duplicate_string(input[i], input_lengths[i]);
            if (unique[unique_count] == NULL) {
                free(unique_lengths);
                free_string_list(unique, unique_count);
                return -1;
            }

            unique_lengths[unique_count] = input_lengths[i];
            ++unique_count;
        }
    }

    free(unique_lengths);
    *output = unique;
    *output_count = unique_count;

    return 0;
}

int main(void)
{
    static const char word_apple[] = "apple";
    static const char word_banana[] = "banana";
    static const char word_orange[] = "orange";
    static const char word_grape[] = "grape";

    const char *words[] = {
        word_apple,
        word_banana,
        word_apple,
        word_orange,
        word_banana,
        word_grape
    };

    const size_t word_lengths[] = {
        sizeof(word_apple) - 1U,
        sizeof(word_banana) - 1U,
        sizeof(word_apple) - 1U,
        sizeof(word_orange) - 1U,
        sizeof(word_banana) - 1U,
        sizeof(word_grape) - 1U
    };

    const size_t word_count = sizeof(words) / sizeof(words[0]);
    char **unique_words = NULL;
    size_t unique_count = 0U;

    if (remove_duplicate_words(words, word_lengths, word_count,
                               &unique_words, &unique_count) != 0) {
        fputs("Failed to remove duplicate words.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < unique_count; ++i) {
        if (puts(unique_words[i]) == EOF) {
            free_string_list(unique_words, unique_count);
            return EXIT_FAILURE;
        }
    }

    free_string_list(unique_words, unique_count);
    return EXIT_SUCCESS;
}