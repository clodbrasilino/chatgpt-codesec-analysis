#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void free_string_list(char **list, size_t count)
{
    if (list == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(list[i]);
    }

    free(list);
}

static char *duplicate_string(const char *source, size_t length)
{
    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    char *copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        copy[i] = source[i];
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
    if (output == NULL || output_count == NULL) {
        return -1;
    }

    *output = NULL;
    *output_count = 0;

    if (input_count == 0) {
        return 0;
    }

    if (input == NULL || input_lengths == NULL ||
        input_count > SIZE_MAX / sizeof(char *) ||
        input_count > SIZE_MAX / sizeof(size_t)) {
        return -1;
    }

    char **unique = calloc(input_count, sizeof(*unique));
    if (unique == NULL) {
        return -1;
    }

    size_t *unique_lengths = malloc(input_count * sizeof(*unique_lengths));
    if (unique_lengths == NULL) {
        free(unique);
        return -1;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < input_count; ++i) {
        if (input[i] == NULL || input_lengths[i] == SIZE_MAX) {
            free(unique_lengths);
            free_string_list(unique, unique_count);
            return -1;
        }

        int found = 0;

        for (size_t j = 0; j < unique_count; ++j) {
            if (input_lengths[i] == unique_lengths[j] &&
                memcmp(input[i], unique[j], input_lengths[i]) == 0) {
                found = 1;
                break;
            }
        }

        if (!found) {
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
        sizeof(word_apple) - 1,
        sizeof(word_banana) - 1,
        sizeof(word_apple) - 1,
        sizeof(word_orange) - 1,
        sizeof(word_banana) - 1,
        sizeof(word_grape) - 1
    };

    const size_t word_count = sizeof(words) / sizeof(words[0]);
    char **unique_words = NULL;
    size_t unique_count = 0;

    if (remove_duplicate_words(words, word_lengths, word_count,
                               &unique_words, &unique_count) != 0) {
        fputs("Failed to remove duplicate words.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < unique_count; ++i) {
        if (puts(unique_words[i]) == EOF) {
            free_string_list(unique_words, unique_count);
            return EXIT_FAILURE;
        }
    }

    free_string_list(unique_words, unique_count);
    return EXIT_SUCCESS;
}