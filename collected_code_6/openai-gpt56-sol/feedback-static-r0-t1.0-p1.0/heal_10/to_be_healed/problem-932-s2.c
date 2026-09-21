#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void free_strings(char **strings, size_t count)
{
    if (strings == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(strings[i]);
    }

    free(strings);
}

static char *duplicate_string(const char *source, size_t length)
{
    if (source == NULL || length > SIZE_MAX - 1) {
        return NULL;
    }

    size_t allocation_size = length + 1;
    char *copy = malloc(allocation_size);

    if (copy == NULL) {
        return NULL;
    }

    if (length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static int remove_duplicate_words(const char *const input[],
                                  size_t input_count,
                                  size_t max_word_length,
                                  char ***output,
                                  size_t *output_count)
{
    char **unique = NULL;
    size_t *unique_lengths = NULL;
    size_t unique_count = 0;

    if (output == NULL || output_count == NULL) {
        return -1;
    }

    *output = NULL;
    *output_count = 0;

    if ((input == NULL && input_count != 0) || max_word_length == 0) {
        return -1;
    }

    if (input_count == 0) {
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

    for (size_t i = 0; i < input_count; ++i) {
        if (input[i] == NULL) {
            free(unique_lengths);
            free_strings(unique, unique_count);
            return -1;
        }

        const char *terminator = memchr(input[i], '\0', max_word_length);
        if (terminator == NULL) {
            free(unique_lengths);
            free_strings(unique, unique_count);
            return -1;
        }

        size_t input_length = (size_t)(terminator - input[i]);
        int duplicate = 0;

        for (size_t j = 0; j < unique_count; ++j) {
            if (input_length == unique_lengths[j] &&
                (input_length == 0 ||
                 memcmp(input[i], unique[j], input_length) == 0)) {
                duplicate = 1;
                break;
            }
        }

        if (!duplicate) {
            char *copy = duplicate_string(input[i], input_length);
            if (copy == NULL) {
                free(unique_lengths);
                free_strings(unique, unique_count);
                return -1;
            }

            unique[unique_count] = copy;
            unique_lengths[unique_count] = input_length;
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
    const char *words[] = {
        "apple",
        "banana",
        "apple",
        "orange",
        "banana",
        "grape",
        "orange"
    };

    const size_t word_count = sizeof(words) / sizeof(words[0]);
    const size_t max_word_length = 256;
    char **unique_words = NULL;
    size_t unique_count = 0;

    if (remove_duplicate_words(words,
                               word_count,
                               max_word_length,
                               &unique_words,
                               &unique_count) != 0) {
        fputs("Failed to remove duplicate words.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < unique_count; ++i) {
        if (puts(unique_words[i]) == EOF) {
            free_strings(unique_words, unique_count);
            return EXIT_FAILURE;
        }
    }

    free_strings(unique_words, unique_count);
    return EXIT_SUCCESS;
}