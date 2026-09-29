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

static char *duplicate_string(const char *source, size_t max_length)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || max_length == 0) {
        return NULL;
    }

    terminator = memchr(source, '\0', max_length);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);
    if (length == SIZE_MAX) {
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

static int remove_duplicate_words(const char *const input[],
                                  size_t input_count,
                                  size_t max_word_length,
                                  char ***output,
                                  size_t *output_count)
{
    char **unique;
    size_t unique_count = 0;

    if (output == NULL || output_count == NULL) {
        return -1;
    }

    *output = NULL;
    *output_count = 0;

    if ((input == NULL && input_count != 0) ||
        max_word_length == 0 ||
        input_count > SIZE_MAX / sizeof(*unique)) {
        return -1;
    }

    if (input_count == 0) {
        return 0;
    }

    unique = calloc(input_count, sizeof(*unique));
    if (unique == NULL) {
        return -1;
    }

    for (size_t i = 0; i < input_count; ++i) {
        const char *terminator;
        size_t input_length;
        int duplicate = 0;

        if (input[i] == NULL) {
            free_strings(unique, unique_count);
            return -1;
        }

        terminator = memchr(input[i], '\0', max_word_length);
        if (terminator == NULL) {
            free_strings(unique, unique_count);
            return -1;
        }

        input_length = (size_t)(terminator - input[i]);

        for (size_t j = 0; j < unique_count; ++j) {
            size_t unique_length = strlen(unique[j]);

            if (input_length == unique_length &&
                memcmp(input[i], unique[j], input_length) == 0) {
                duplicate = 1;
                break;
            }
        }

        if (!duplicate) {
            unique[unique_count] =
                duplicate_string(input[i], max_word_length);

            if (unique[unique_count] == NULL) {
                free_strings(unique, unique_count);
                return -1;
            }

            ++unique_count;
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