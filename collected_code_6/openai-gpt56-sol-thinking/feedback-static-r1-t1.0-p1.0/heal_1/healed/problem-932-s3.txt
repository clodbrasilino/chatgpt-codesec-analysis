#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum RemoveResult {
    REMOVE_SUCCESS,
    REMOVE_INVALID_ARGUMENT,
    REMOVE_OUT_OF_MEMORY
};

static void free_string_list(char **list, size_t count)
{
    size_t i;

    for (i = 0; i < count; ++i) {
        free(list[i]);
    }

    free(list);
}

static char *copy_string(const char *source)
{
    size_t length;
    char *copy;

    length = strlen(source);
    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length + 1);
    return copy;
}

static enum RemoveResult remove_duplicate_words(
    const char *const words[],
    size_t word_count,
    char ***unique_words,
    size_t *unique_count)
{
    char **result;
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

    if (words == NULL || word_count > SIZE_MAX / sizeof(*result)) {
        return REMOVE_INVALID_ARGUMENT;
    }

    result = calloc(word_count, sizeof(*result));
    if (result == NULL) {
        return REMOVE_OUT_OF_MEMORY;
    }

    result_count = 0;

    for (i = 0; i < word_count; ++i) {
        int duplicate = 0;

        if (words[i] == NULL) {
            free_string_list(result, result_count);
            return REMOVE_INVALID_ARGUMENT;
        }

        for (j = 0; j < result_count; ++j) {
            if (strcmp(words[i], result[j]) == 0) {
                duplicate = 1;
                break;
            }
        }

        if (!duplicate) {
            result[result_count] = copy_string(words[i]);
            if (result[result_count] == NULL) {
                free_string_list(result, result_count);
                return REMOVE_OUT_OF_MEMORY;
            }

            ++result_count;
        }
    }

    *unique_words = result;
    *unique_count = result_count;
    return REMOVE_SUCCESS;
}

int main(void)
{
    const char *words[] = {
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