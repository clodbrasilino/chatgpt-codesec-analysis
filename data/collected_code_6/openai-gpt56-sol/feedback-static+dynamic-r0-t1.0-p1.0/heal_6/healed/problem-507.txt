#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int is_word_to_remove(const char *word,
                             const char *const words_to_remove[],
                             size_t remove_count)
{
    size_t i;

    if (word == NULL || (remove_count > 0 && words_to_remove == NULL)) {
        return 0;
    }

    for (i = 0; i < remove_count; ++i) {
        if (words_to_remove[i] != NULL &&
            strcmp(word, words_to_remove[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

static size_t remove_words(char *words[],
                           size_t word_count,
                           const char *const words_to_remove[],
                           size_t remove_count)
{
    size_t read_index;
    size_t write_index = 0;

    if (words == NULL || (remove_count > 0 && words_to_remove == NULL)) {
        return word_count;
    }

    for (read_index = 0; read_index < word_count; ++read_index) {
        char *word = words[read_index];

        if (word == NULL) {
            continue;
        }

        if (is_word_to_remove(word, words_to_remove, remove_count)) {
            free(word);
        } else {
            words[write_index++] = word;
        }
    }

    for (read_index = write_index; read_index < word_count; ++read_index) {
        words[read_index] = NULL;
    }

    return write_index;
}

static char *duplicate_string(const char *source, size_t source_size)
{
    const char *terminator;
    size_t length;
    size_t allocation_size;
    char *copy;

    if (source == NULL || source_size == 0) {
        return NULL;
    }

    terminator = memchr(source, '\0', source_size);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);

    if (length == SIZE_MAX) {
        return NULL;
    }

    allocation_size = length + 1;
    copy = malloc(allocation_size);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, allocation_size);

    return copy;
}

static void free_word_list(char *words[], size_t word_count)
{
    size_t i;

    if (words == NULL) {
        return;
    }

    for (i = 0; i < word_count; ++i) {
        free(words[i]);
        words[i] = NULL;
    }
}

int main(void)
{
    static const char initial_words[][7] = {
        "apple", "banana", "orange", "banana", "grape", "pear"
    };
    static const char *const words_to_remove[] = {
        "banana", "pear"
    };
    const size_t word_count =
        sizeof(initial_words) / sizeof(initial_words[0]);
    const size_t remove_count =
        sizeof(words_to_remove) / sizeof(words_to_remove[0]);
    char **words;
    size_t count;
    size_t i;

    if (word_count > SIZE_MAX / sizeof(*words)) {
        fputs("Word list is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    words = calloc(word_count, sizeof(*words));
    if (words == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < word_count; ++i) {
        words[i] = duplicate_string(initial_words[i],
                                    sizeof(initial_words[i]));
        if (words[i] == NULL) {
            fputs("Failed to duplicate a word.\n", stderr);
            free_word_list(words, i);
            free(words);
            return EXIT_FAILURE;
        }
    }

    count = remove_words(words, word_count,
                         words_to_remove, remove_count);

    for (i = 0; i < count; ++i) {
        if (puts(words[i]) == EOF) {
            fputs("Failed to write output.\n", stderr);
            free_word_list(words, count);
            free(words);
            return EXIT_FAILURE;
        }
    }

    free_word_list(words, count);
    free(words);

    return EXIT_SUCCESS;
}