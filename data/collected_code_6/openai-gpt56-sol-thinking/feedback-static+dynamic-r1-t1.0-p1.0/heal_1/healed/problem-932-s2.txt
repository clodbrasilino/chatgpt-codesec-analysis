#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *data;
    size_t length;
} word_view;

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

static bool remove_duplicate_words(const word_view *words, size_t count,
                                   char ***result, size_t *result_count)
{
    char **unique_words;
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

    if (words == NULL || count > SIZE_MAX / sizeof(*unique_words)) {
        return false;
    }

    for (i = 0; i < count; ++i) {
        if (words[i].data == NULL ||
            words[i].length == SIZE_MAX ||
            memchr(words[i].data, '\0', words[i].length) != NULL) {
            return false;
        }
    }

    unique_words = malloc(count * sizeof(*unique_words));
    if (unique_words == NULL) {
        return false;
    }

    for (i = 0; i < count; ++i) {
        bool duplicate = false;

        for (j = 0; j < i; ++j) {
            if (words[i].length == words[j].length &&
                memcmp(words[i].data, words[j].data, words[i].length) == 0) {
                duplicate = true;
                break;
            }
        }

        if (!duplicate) {
            size_t k;

            unique_words[unique_count] = malloc(words[i].length + 1);
            if (unique_words[unique_count] == NULL) {
                free_word_list(unique_words, unique_count);
                return false;
            }

            for (k = 0; k < words[i].length; ++k) {
                unique_words[unique_count][k] = words[i].data[k];
            }

            unique_words[unique_count][words[i].length] = '\0';
            ++unique_count;
        }
    }

    *result = unique_words;
    *result_count = unique_count;
    return true;
}

int main(void)
{
    static const word_view words[] = {
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