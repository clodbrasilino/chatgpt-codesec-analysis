#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void free_word_list(char **words, size_t count)
{
    if (words == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(words[i]);
    }

    free(words);
}

static char *duplicate_string(const char *source, size_t source_size)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || source_size == 0) {
        return NULL;
    }

    terminator = memchr(source, '\0', source_size);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);

    if (length > SIZE_MAX - 1) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length + 1);
    return copy;
}

static int should_remove(const char *word,
                         const char *const remove_words[],
                         size_t remove_count)
{
    if (word == NULL || (remove_count != 0 && remove_words == NULL)) {
        return 0;
    }

    for (size_t i = 0; i < remove_count; ++i) {
        if (remove_words[i] != NULL &&
            strcmp(word, remove_words[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

static int remove_words(const char *const input_words[],
                        const size_t input_sizes[],
                        size_t input_count,
                        const char *const remove_list[],
                        size_t remove_count,
                        char ***result,
                        size_t *result_count)
{
    char **filtered;
    size_t kept = 0;

    if (result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if ((input_count != 0 &&
         (input_words == NULL || input_sizes == NULL)) ||
        (remove_count != 0 && remove_list == NULL)) {
        return -1;
    }

    if (input_count == 0) {
        return 0;
    }

    if (input_count > SIZE_MAX / sizeof(*filtered)) {
        return -1;
    }

    filtered = calloc(input_count, sizeof(*filtered));
    if (filtered == NULL) {
        return -1;
    }

    for (size_t i = 0; i < input_count; ++i) {
        if (input_words[i] == NULL ||
            input_sizes[i] == 0 ||
            memchr(input_words[i], '\0', input_sizes[i]) == NULL) {
            free_word_list(filtered, kept);
            return -1;
        }

        if (!should_remove(input_words[i], remove_list, remove_count)) {
            filtered[kept] =
                duplicate_string(input_words[i], input_sizes[i]);

            if (filtered[kept] == NULL) {
                free_word_list(filtered, kept);
                return -1;
            }

            ++kept;
        }
    }

    if (kept == 0) {
        free(filtered);
        filtered = NULL;
    } else {
        char **resized;

        if (kept > SIZE_MAX / sizeof(*filtered)) {
            free_word_list(filtered, kept);
            return -1;
        }

        resized = realloc(filtered, kept * sizeof(*filtered));
        if (resized != NULL) {
            filtered = resized;
        }
    }

    *result = filtered;
    *result_count = kept;
    return 0;
}

int main(void)
{
    const char *words[] = {
        "apple",
        "banana",
        "orange",
        "banana",
        "grape",
        "pear"
    };
    const size_t word_sizes[] = {
        sizeof("apple"),
        sizeof("banana"),
        sizeof("orange"),
        sizeof("banana"),
        sizeof("grape"),
        sizeof("pear")
    };
    const char *remove_list[] = {
        "banana",
        "pear"
    };
    char **filtered = NULL;
    size_t filtered_count = 0;

    if (remove_words(words,
                     word_sizes,
                     sizeof(words) / sizeof(words[0]),
                     remove_list,
                     sizeof(remove_list) / sizeof(remove_list[0]),
                     &filtered,
                     &filtered_count) != 0) {
        fputs("Failed to remove words.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < filtered_count; ++i) {
        if (puts(filtered[i]) == EOF) {
            free_word_list(filtered, filtered_count);
            return EXIT_FAILURE;
        }
    }

    free_word_list(filtered, filtered_count);
    return EXIT_SUCCESS;
}