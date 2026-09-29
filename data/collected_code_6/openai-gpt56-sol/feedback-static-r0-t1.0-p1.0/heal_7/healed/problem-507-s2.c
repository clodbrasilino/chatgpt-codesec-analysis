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

    if (length > SIZE_MAX - 1) {
        return NULL;
    }

    allocation_size = length + 1;
    copy = malloc(allocation_size);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0) {
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    return copy;
}

static void free_words(char *words[], size_t count)
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

int main(void)
{
    static const char initial_words[][7] = {
        "apple", "banana", "orange", "banana", "grape", "pear"
    };
    static const char *const remove_list[] = {
        "banana", "pear"
    };
    const size_t initial_count =
        sizeof(initial_words) / sizeof(initial_words[0]);
    const size_t remove_count =
        sizeof(remove_list) / sizeof(remove_list[0]);
    char **words;
    size_t remaining_count;
    size_t i;

    if (initial_count > SIZE_MAX / sizeof(*words)) {
        fputs("Memory allocation size overflow.\n", stderr);
        return EXIT_FAILURE;
    }

    words = calloc(initial_count, sizeof(*words));
    if (words == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < initial_count; ++i) {
        words[i] = duplicate_string(initial_words[i],
                                    sizeof(initial_words[i]));
        if (words[i] == NULL) {
            free_words(words, i);
            fputs("Invalid string or memory allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    remaining_count =
        remove_words(words, initial_count, remove_list, remove_count);

    for (i = 0; i < remaining_count; ++i) {
        const char *separator =
            (i + 1 < remaining_count) ? " " : "\n";

        if (printf("%s%s", words[i], separator) < 0) {
            free_words(words, remaining_count);
            return EXIT_FAILURE;
        }
    }

    if (remaining_count == 0 && putchar('\n') == EOF) {
        free_words(words, remaining_count);
        return EXIT_FAILURE;
    }

    free_words(words, remaining_count);
    return EXIT_SUCCESS;
}