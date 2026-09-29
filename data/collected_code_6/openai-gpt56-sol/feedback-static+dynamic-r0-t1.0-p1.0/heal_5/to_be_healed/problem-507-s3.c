#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void free_word_list(char **words, size_t count)
{
    if (words == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(words[i]);
    }

    free(words);
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

    if (length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static int should_remove(const char *word,
                         size_t word_length,
                         const char *const remove_words[],
                         const size_t remove_lengths[],
                         size_t remove_count)
{
    if (word == NULL ||
        (remove_count > 0 &&
         (remove_words == NULL || remove_lengths == NULL))) {
        return 0;
    }

    for (size_t i = 0; i < remove_count; ++i) {
        if (remove_words[i] != NULL &&
            remove_lengths[i] == word_length &&
            (word_length == 0 ||
             memcmp(word, remove_words[i], word_length) == 0)) {
            return 1;
        }
    }

    return 0;
}

static int remove_words(const char *const input_words[],
                        const size_t input_lengths[],
                        size_t input_count,
                        const char *const remove_list[],
                        const size_t remove_lengths[],
                        size_t remove_count,
                        char ***result,
                        size_t *result_count)
{
    char **filtered;
    size_t kept = 0;

    if (result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if ((input_count > 0 &&
         (input_words == NULL || input_lengths == NULL)) ||
        (remove_count > 0 &&
         (remove_list == NULL || remove_lengths == NULL))) {
        return -1;
    }

    if (input_count == 0) {
        return 0;
    }

    if (input_count > SIZE_MAX / sizeof(*filtered)) {
        return -1;
    }

    filtered = calloc(input_count, sizeof(*filtered));
    if (filtered == NULL) {
        return -1;
    }

    for (size_t i = 0; i < input_count; ++i) {
        if (input_words[i] == NULL ||
            input_lengths[i] == SIZE_MAX) {
            free_word_list(filtered, kept);
            return -1;
        }

        if (!should_remove(input_words[i],
                           input_lengths[i],
                           remove_list,
                           remove_lengths,
                           remove_count)) {
            filtered[kept] =
                duplicate_string(input_words[i], input_lengths[i]);

            if (filtered[kept] == NULL) {
                free_word_list(filtered, kept);
                return -1;
            }

            ++kept;
        }
    }

    if (kept == 0) {
        free(filtered);
        filtered = NULL;
    } else {
        char **resized;

        if (kept > SIZE_MAX / sizeof(*filtered)) {
            free_word_list(filtered, kept);
            return -1;
        }

        resized = realloc(filtered, kept * sizeof(*filtered));
        if (resized != NULL) {
            filtered = resized;
        }
    }

    *result = filtered;
    *result_count = kept;
    return 0;
}

int main(void)
{
    static const char *const words[] = {
        "apple", "banana", "orange", "banana", "grape", "pear"
    };
    static const size_t word_lengths[] = {
        sizeof("apple") - 1,
        sizeof("banana") - 1,
        sizeof("orange") - 1,
        sizeof("banana") - 1,
        sizeof("grape") - 1,
        sizeof("pear") - 1
    };
    static const char *const remove_list[] = {
        "banana", "pear"
    };
    static const size_t remove_lengths[] = {
        sizeof("banana") - 1,
        sizeof("pear") - 1
    };
    char **filtered = NULL;
    size_t filtered_count = 0;

    if (remove_words(words,
                     word_lengths,
                     sizeof(words) / sizeof(words[0]),
                     remove_list,
                     remove_lengths,
                     sizeof(remove_list) / sizeof(remove_list[0]),
                     &filtered,
                     &filtered_count) != 0) {
        fputs("Failed to remove words.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < filtered_count; ++i) {
        if (puts(filtered[i]) == EOF) {
            free_word_list(filtered, filtered_count);
            return EXIT_FAILURE;
        }
    }

    free_word_list(filtered, filtered_count);
    return EXIT_SUCCESS;
}