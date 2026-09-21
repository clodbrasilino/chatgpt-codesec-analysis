#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void free_word_list(char **words, size_t count)
{
    size_t i;

    if (words == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free(words[i]);
    }

    free(words);
}

static bool remove_duplicate_words(const char *const *words, size_t count,
                                   char ***result, size_t *result_count)
{
    char **unique_words;
    size_t unique_count;
    size_t i;
    size_t j;

    if (result == NULL || result_count == NULL) {
        return false;
    }

    *result = NULL;
    *result_count = 0;

    if (count == 0) {
        return true;
    }

    if (words == NULL || count > SIZE_MAX / sizeof(*unique_words)) {
        return false;
    }

    for (i = 0; i < count; ++i) {
        if (words[i] == NULL) {
            return false;
        }
    }

    unique_words = malloc(count * sizeof(*unique_words));
    if (unique_words == NULL) {
        return false;
    }

    unique_count = 0;

    for (i = 0; i < count; ++i) {
        bool duplicate = false;

        for (j = 0; j < unique_count; ++j) {
            if (strcmp(words[i], unique_words[j]) == 0) {
                duplicate = true;
                break;
            }
        }

        if (!duplicate) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t length = strlen(words[i]);

            if (length == SIZE_MAX) {
                free_word_list(unique_words, unique_count);
                return false;
            }

            unique_words[unique_count] = malloc(length + 1);
            if (unique_words[unique_count] == NULL) {
                free_word_list(unique_words, unique_count);
                return false;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(unique_words[unique_count], words[i], length + 1);
            ++unique_count;
        }
    }

    *result = unique_words;
    *result_count = unique_count;
    return true;
}

int main(void)
{
    const char *const words[] = {
        "apple",
        "banana",
        "orange",
        "apple",
        "grape",
        "banana",
        "pear"
    };
    char **unique_words;
    size_t unique_count;
    size_t i;

    if (!remove_duplicate_words(words, sizeof(words) / sizeof(words[0]),
                                &unique_words, &unique_count)) {
        fputs("Failed to remove duplicate words.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < unique_count; ++i) {
        if (fputs(unique_words[i], stdout) == EOF ||
            fputc('\n', stdout) == EOF) {
            free_word_list(unique_words, unique_count);
            return EXIT_FAILURE;
        }
    }

    free_word_list(unique_words, unique_count);
    return EXIT_SUCCESS;
}