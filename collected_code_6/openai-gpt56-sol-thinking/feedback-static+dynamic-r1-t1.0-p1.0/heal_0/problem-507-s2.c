#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool remove_words(const char **list,
                  size_t list_count,
                  const char *const *words_to_remove,
                  size_t removal_count,
                  size_t *new_count)
{
    size_t read_index;
    size_t write_index = 0;

    if (new_count == NULL ||
        (list_count > 0 && list == NULL) ||
        (removal_count > 0 && words_to_remove == NULL)) {
        return false;
    }

    for (read_index = 0; read_index < list_count; ++read_index) {
        if (list[read_index] == NULL) {
            return false;
        }
    }

    for (read_index = 0; read_index < removal_count; ++read_index) {
        if (words_to_remove[read_index] == NULL) {
            return false;
        }
    }

    for (read_index = 0; read_index < list_count; ++read_index) {
        size_t removal_index;
        bool should_remove = false;

        for (removal_index = 0; removal_index < removal_count; ++removal_index) {
            if (strcmp(list[read_index], words_to_remove[removal_index]) == 0) {
                should_remove = true;
                break;
            }
        }

        if (!should_remove) {
            list[write_index] = list[read_index];
            ++write_index;
        }
    }

    for (read_index = write_index; read_index < list_count; ++read_index) {
        list[read_index] = NULL;
    }

    *new_count = write_index;
    return true;
}

int main(void)
{
    const char *words[] = {
        "apple", "banana", "orange", "grape",
        "banana", "pear", "apple", "melon"
    };
    const char *const words_to_remove[] = {
        "apple", "banana"
    };
    const size_t word_count = sizeof(words) / sizeof(words[0]);
    const size_t removal_count =
        sizeof(words_to_remove) / sizeof(words_to_remove[0]);
    size_t remaining_count;
    size_t index;

    if (!remove_words(words,
                      word_count,
                      words_to_remove,
                      removal_count,
                      &remaining_count)) {
        return EXIT_FAILURE;
    }

    for (index = 0; index < remaining_count; ++index) {
        if (printf("%s%s",
                   words[index],
                   index + 1 < remaining_count ? " " : "\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    if (remaining_count == 0 && putchar('\n') == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}