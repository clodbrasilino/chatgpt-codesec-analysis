#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

static char *copy_string(const char *source)
{
    size_t length;
    char *copy;

    if (source == NULL) {
        return NULL;
    }

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

static int remove_duplicate_words(char *const *words, size_t count,
                                  char ***result, size_t *result_count)
{
    char **unique_words;
    size_t unique_count = 0;
    size_t i;
    size_t j;

    if (result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if (count == 0) {
        return 0;
    }

    if (words == NULL || count > SIZE_MAX / sizeof(*unique_words)) {
        return -1;
    }

    unique_words = calloc(count, sizeof(*unique_words));
    if (unique_words == NULL) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        bool duplicate = false;

        if (words[i] == NULL) {
            free_word_list(unique_words, unique_count);
            return -1;
        }

        for (j = 0; j < unique_count; ++j) {
            if (strcmp(words[i], unique_words[j]) == 0) {
                duplicate = true;
                break;
            }
        }

        if (!duplicate) {
            unique_words[unique_count] = copy_string(words[i]);
            if (unique_words[unique_count] == NULL) {
                free_word_list(unique_words, unique_count);
                return -1;
            }
            ++unique_count;
        }
    }

    *result = unique_words;
    *result_count = unique_count;
    return 0;
}

int main(int argc, char *argv[])
{
    char **unique_words = NULL;
    size_t unique_count = 0;
    size_t input_count;
    size_t i;
    int status = EXIT_SUCCESS;

    input_count = argc > 1 ? (size_t)(argc - 1) : 0;

    if (remove_duplicate_words(argv + 1, input_count,
                               &unique_words, &unique_count) != 0) {
        fputs("Failed to remove duplicate words.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < unique_count; ++i) {
        if (i > 0 && fputc(' ', stdout) == EOF) {
            status = EXIT_FAILURE;
            break;
        }

        if (fputs(unique_words[i], stdout) == EOF) {
            status = EXIT_FAILURE;
            break;
        }
    }

    if (status == EXIT_SUCCESS && fputc('\n', stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    free_word_list(unique_words, unique_count);
    return status;
}