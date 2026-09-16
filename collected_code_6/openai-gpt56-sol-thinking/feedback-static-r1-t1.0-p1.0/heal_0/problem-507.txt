#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int remove_words(const char **list, size_t *list_count,
                        const char *const *words, size_t word_count)
{
    size_t read_index;
    size_t write_index = 0;

    if (list == NULL || list_count == NULL ||
        (word_count > 0 && words == NULL)) {
        return -1;
    }

    for (read_index = 0; read_index < *list_count; ++read_index) {
        size_t word_index;
        int remove = 0;

        if (list[read_index] == NULL) {
            return -1;
        }

        for (word_index = 0; word_index < word_count; ++word_index) {
            if (words[word_index] == NULL) {
                return -1;
            }

            if (strcmp(list[read_index], words[word_index]) == 0) {
                remove = 1;
                break;
            }
        }

        if (!remove) {
            list[write_index++] = list[read_index];
        }
    }

    *list_count = write_index;
    return 0;
}

int main(void)
{
    const char *list[] = {
        "apple",
        "banana",
        "orange",
        "banana",
        "grape",
        "apple",
        "mango"
    };
    const char *words_to_remove[] = {
        "apple",
        "banana"
    };
    size_t list_count = sizeof(list) / sizeof(list[0]);
    const size_t word_count =
        sizeof(words_to_remove) / sizeof(words_to_remove[0]);
    size_t index;

    if (remove_words(list, &list_count, words_to_remove, word_count) != 0) {
        fputs("Failed to remove words.\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0; index < list_count; ++index) {
        puts(list[index]);
    }

    return EXIT_SUCCESS;
}