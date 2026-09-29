#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int most_frequent_word(const char *const words[], size_t count,
                       const char **result, size_t *occurrences)
{
    size_t highest_count = 0;
    const char *most_frequent = NULL;

    if (words == NULL || result == NULL || occurrences == NULL || count == 0) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        size_t current_count = 0;

        if (words[i] == NULL) {
            return -1;
        }

        for (size_t j = 0; j < count; ++j) {
            if (words[j] == NULL) {
                return -1;
            }

            if (strcmp(words[i], words[j]) == 0) {
                ++current_count;
            }
        }

        if (current_count > highest_count) {
            highest_count = current_count;
            most_frequent = words[i];
        }
    }

    *result = most_frequent;
    *occurrences = highest_count;
    return 0;
}

int main(int argc, char *argv[])
{
    const char *result = NULL;
    size_t occurrences = 0;

    if (argc < 2) {
        if (fprintf(stderr, "Usage: %s word [word ...]\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (most_frequent_word((const char *const *)&argv[1],
                           (size_t)(argc - 1),
                           &result,
                           &occurrences) != 0) {
        if (fprintf(stderr, "Unable to determine the most frequent word.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("%s: %zu\n", result, occurrences) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}