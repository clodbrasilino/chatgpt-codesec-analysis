#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool remove_words(const char *words[], size_t word_count,
                  const char *const words_to_remove[], size_t remove_count,
                  size_t *remaining_count)
{
    size_t read_index;
    size_t write_index = 0;

    if (remaining_count == NULL ||
        (word_count > 0 && words == NULL) ||
        (remove_count > 0 && words_to_remove == NULL)) {
        return false;
    }

    *remaining_count = 0;

    for (read_index = 0; read_index < word_count; ++read_index) {
        if (words[read_index] == NULL) {
            return false;
        }
    }

    for (read_index = 0; read_index < remove_count; ++read_index) {
        if (words_to_remove[read_index] == NULL) {
            return false;
        }
    }

    for (read_index = 0; read_index < word_count; ++read_index) {
        size_t remove_index;
        bool should_remove = false;

        for (remove_index = 0; remove_index < remove_count; ++remove_index) {
            if (strcmp(words[read_index], words_to_remove[remove_index]) == 0) {
                should_remove = true;
                break;
            }
        }

        if (!should_remove) {
            words[write_index++] = words[read_index];
        }
    }

    for (read_index = write_index; read_index < word_count; ++read_index) {
        words[read_index] = NULL;
    }

    *remaining_count = write_index;
    return true;
}

int main(void)
{
    const char *words[] = {
        "apple", "banana", "orange", "apple", "grape", "banana", "pear"
    };
    const char *words_to_remove[] = {
        "apple", "banana"
    };
    const size_t word_count = sizeof words / sizeof words[0];
    const size_t remove_count =
        sizeof words_to_remove / sizeof words_to_remove[0];
    size_t remaining_count;
    size_t index;

    if (!remove_words(words, word_count, words_to_remove, remove_count,
                      &remaining_count)) {
        if (fputs("Unable to remove words.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (index = 0; index < remaining_count; ++index) {
        if (puts(words[index]) == EOF) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}