#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct word_view {
    const char *data;
    size_t length;
};

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

static bool remove_duplicate_words(const struct word_view *words,
                                   size_t count,
                                   char ***result,
                                   size_t *result_count)
{
    char **unique_words;
    size_t *unique_lengths;
    size_t unique_count = 0;
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

    if (words == NULL ||
        count > SIZE_MAX / sizeof(*unique_words) ||
        count > SIZE_MAX / sizeof(*unique_lengths)) {
        return false;
    }

    for (i = 0; i < count; ++i) {
        if (words[i].data == NULL || words[i].length == SIZE_MAX) {
            return false;
        }
    }

    unique_words = malloc(count * sizeof(*unique_words));
    if (unique_words == NULL) {
        return false;
    }

    unique_lengths = malloc(count * sizeof(*unique_lengths));
    if (unique_lengths == NULL) {
        free(unique_words);
        return false;
    }

    for (i = 0; i < count; ++i) {
        bool duplicate = false;

        for (j = 0; j < unique_count; ++j) {
            if (words[i].length == unique_lengths[j] &&
                memcmp(words[i].data, unique_words[j],
                       words[i].length) == 0) {
                duplicate = true;
                break;
            }
        }

        if (!duplicate) {
            char *copy = malloc(words[i].length + 1);

            if (copy == NULL) {
                free(unique_lengths);
                free_word_list(unique_words, unique_count);
                return false;
            }

            if (words[i].length != 0) {
                memcpy(copy, words[i].data, words[i].length);
            }

            copy[words[i].length] = '\0';
            unique_words[unique_count] = copy;
            unique_lengths[unique_count] = words[i].length;
            ++unique_count;
        }
    }

    free(unique_lengths);
    *result = unique_words;
    *result_count = unique_count;
    return true;
}

int main(void)
{
    static const struct word_view words[] = {
        {"apple", sizeof("apple") - 1},
        {"banana", sizeof("banana") - 1},
        {"orange", sizeof("orange") - 1},
        {"apple", sizeof("apple") - 1},
        {"grape", sizeof("grape") - 1},
        {"banana", sizeof("banana") - 1},
        {"pear", sizeof("pear") - 1}
    };
    char **unique_words;
    size_t unique_count;
    size_t i;

    if (!remove_duplicate_words(words,
                                sizeof(words) / sizeof(words[0]),
                                &unique_words,
                                &unique_count)) {
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