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
    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    size_t allocation_size = length + 1;
    char *copy = malloc(allocation_size);

    if (copy == NULL) {
        return NULL;
    }

    if (length != 0) {
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
    char **unique = NULL;
    size_t *unique_lengths = NULL;
    size_t unique_count = 0;

    if (output == NULL || output_count == NULL) {
        return -1;
    }

    *output = NULL;
    *output_count = 0;

    if (input_count == 0) {
        return 0;
    }

    if (input == NULL ||
        input_lengths == NULL ||
        input_count > SIZE_MAX / sizeof(*unique) ||
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
        int duplicate = 0;

        if (input[i] == NULL || input_lengths[i] == SIZE_MAX) {
            free(unique_lengths);
            free_strings(unique, unique_count);
            return -1;
        }

        for (size_t j = 0; j < unique_count; ++j) {
            if (input_lengths[i] == unique_lengths[j] &&
                (input_lengths[i] == 0 ||
                 memcmp(input[i], unique[j], input_lengths[i]) == 0)) {
                duplicate = 1;
                break;
            }
        }

        if (!duplicate) {
            char *copy = duplicate_string(input[i], input_lengths[i]);

            if (copy == NULL) {
                free(unique_lengths);
                free_strings(unique, unique_count);
                return -1;
            }

            unique[unique_count] = copy;
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
    static const char apple[] = "apple";
    static const char banana[] = "banana";
    static const char orange[] = "orange";
    static const char grape[] = "grape";

    const char *words[] = {
        apple,
        banana,
        apple,
        orange,
        banana,
        grape,
        orange
    };

    const size_t word_lengths[] = {
        sizeof(apple) - 1,
        sizeof(banana) - 1,
        sizeof(apple) - 1,
        sizeof(orange) - 1,
        sizeof(banana) - 1,
        sizeof(grape) - 1,
        sizeof(orange) - 1
    };

    const size_t word_count = sizeof(words) / sizeof(words[0]);
    char **unique_words = NULL;
    size_t unique_count = 0;

    if (remove_duplicate_words(words,
                               word_lengths,
                               word_count,
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