#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_removed(const char *word,
                      const char *const remove_words[],
                      size_t remove_count)
{
    size_t i;

    if (word == NULL || (remove_count != 0 && remove_words == NULL)) {
        return 0;
    }

    for (i = 0; i < remove_count; ++i) {
        if (remove_words[i] != NULL &&
            strcmp(word, remove_words[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

static size_t remove_words(char *words[],
                           size_t word_count,
                           const char *const remove_list[],
                           size_t remove_count)
{
    size_t read_index;
    size_t write_index = 0;

    if (words == NULL) {
        return 0;
    }

    for (read_index = 0; read_index < word_count; ++read_index) {
        if (is_removed(words[read_index], remove_list, remove_count)) {
            free(words[read_index]);
        } else {
            words[write_index++] = words[read_index];
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

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0) {
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    return copy;
}

static void free_words(char *words[], size_t word_count)
{
    size_t i;

    if (words == NULL) {
        return;
    }

    for (i = 0; i < word_count; ++i) {
        free(words[i]);
    }

    free(words);
}

int main(void)
{
    static const char *const initial_words[] = {
        "apple", "banana", "orange", "banana", "grape", "pear"
    };
    static const size_t initial_sizes[] = {
        sizeof("apple"),
        sizeof("banana"),
        sizeof("orange"),
        sizeof("banana"),
        sizeof("grape"),
        sizeof("pear")
    };
    static const char *const remove_list[] = {
        "banana", "pear"
    };

    const size_t initial_count =
        sizeof(initial_words) / sizeof(initial_words[0]);
    const size_t size_count =
        sizeof(initial_sizes) / sizeof(initial_sizes[0]);
    const size_t remove_count =
        sizeof(remove_list) / sizeof(remove_list[0]);
    char **words;
    size_t remaining_count;
    size_t i;

    if (initial_count != size_count ||
        initial_count > SIZE_MAX / sizeof(*words)) {
        fputs("Invalid input or allocation size.\n", stderr);
        return EXIT_FAILURE;
    }

    words = calloc(initial_count, sizeof(*words));
    if (words == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < initial_count; ++i) {
        words[i] = duplicate_string(initial_words[i], initial_sizes[i]);
        if (words[i] == NULL) {
            free_words(words, initial_count);
            fputs("Memory allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    remaining_count =
        remove_words(words, initial_count, remove_list, remove_count);

    for (i = 0; i < remaining_count; ++i) {
        if (printf("%s%s",
                   words[i],
                   i + 1 < remaining_count ? " " : "\n") < 0) {
            free_words(words, remaining_count);
            return EXIT_FAILURE;
        }
    }

    free_words(words, remaining_count);
    return EXIT_SUCCESS;
}