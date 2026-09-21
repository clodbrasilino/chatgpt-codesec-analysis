#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum RemoveResult {
    REMOVE_SUCCESS,
    REMOVE_INVALID_ARGUMENT,
    REMOVE_OUT_OF_MEMORY
};

struct Word {
    const char *data;
    size_t length;
};

static void free_string_list(char **list, size_t count)
{
    size_t i;

    for (i = 0; i < count; ++i) {
        free(list[i]);
    }

    free(list);
}

static char *copy_word(const char *source, size_t length)
{
    char *copy;
    size_t i;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    for (i = 0; i < length; ++i) {
        copy[i] = source[i];
    }

    copy[length] = '\0';
    return copy;
}

static int words_equal(
    const char *left,
    size_t left_length,
    const char *right,
    size_t right_length)
{
    size_t i;

    if (left_length != right_length) {
        return 0;
    }

    for (i = 0; i < left_length; ++i) {
        if (left[i] != right[i]) {
            return 0;
        }
    }

    return 1;
}

static enum RemoveResult remove_duplicate_words(
    const struct Word words[],
    size_t word_count,
    char ***unique_words,
    size_t *unique_count)
{
    char **result;
    size_t *result_lengths;
    size_t result_count;
    size_t i;
    size_t j;

    if (unique_words == NULL || unique_count == NULL) {
        return REMOVE_INVALID_ARGUMENT;
    }

    *unique_words = NULL;
    *unique_count = 0;

    if (word_count == 0) {
        return REMOVE_SUCCESS;
    }

    if (words == NULL ||
        word_count > SIZE_MAX / sizeof(*result) ||
        word_count > SIZE_MAX / sizeof(*result_lengths)) {
        return REMOVE_INVALID_ARGUMENT;
    }

    for (i = 0; i < word_count; ++i) {
        if (words[i].data == NULL || words[i].length == SIZE_MAX) {
            return REMOVE_INVALID_ARGUMENT;
        }
    }

    result = malloc(word_count * sizeof(*result));
    if (result == NULL) {
        return REMOVE_OUT_OF_MEMORY;
    }

    result_lengths = malloc(word_count * sizeof(*result_lengths));
    if (result_lengths == NULL) {
        free(result);
        return REMOVE_OUT_OF_MEMORY;
    }

    result_count = 0;

    for (i = 0; i < word_count; ++i) {
        int duplicate = 0;

        for (j = 0; j < result_count; ++j) {
            if (words_equal(
                    words[i].data,
                    words[i].length,
                    result[j],
                    result_lengths[j])) {
                duplicate = 1;
                break;
            }
        }

        if (!duplicate) {
            result[result_count] =
                copy_word(words[i].data, words[i].length);

            if (result[result_count] == NULL) {
                free(result_lengths);
                free_string_list(result, result_count);
                return REMOVE_OUT_OF_MEMORY;
            }

            result_lengths[result_count] = words[i].length;
            ++result_count;
        }
    }

    free(result_lengths);
    *unique_words = result;
    *unique_count = result_count;

    return REMOVE_SUCCESS;
}

int main(void)
{
    const struct Word words[] = {
        { "apple", sizeof("apple") - 1 },
        { "banana", sizeof("banana") - 1 },
        { "orange", sizeof("orange") - 1 },
        { "apple", sizeof("apple") - 1 },
        { "grape", sizeof("grape") - 1 },
        { "banana", sizeof("banana") - 1 },
        { "pear", sizeof("pear") - 1 }
    };
    char **unique_words = NULL;
    size_t unique_count = 0;
    size_t i;
    enum RemoveResult result;

    result = remove_duplicate_words(
        words,
        sizeof(words) / sizeof(words[0]),
        &unique_words,
        &unique_count
    );

    if (result == REMOVE_INVALID_ARGUMENT) {
        fputs("Invalid argument\n", stderr);
        return EXIT_FAILURE;
    }

    if (result == REMOVE_OUT_OF_MEMORY) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < unique_count; ++i) {
        if (puts(unique_words[i]) == EOF) {
            free_string_list(unique_words, unique_count);
            return EXIT_FAILURE;
        }
    }

    free_string_list(unique_words, unique_count);
    return EXIT_SUCCESS;
}