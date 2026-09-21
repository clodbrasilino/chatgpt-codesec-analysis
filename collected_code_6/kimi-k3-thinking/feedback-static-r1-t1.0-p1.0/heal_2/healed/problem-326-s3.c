#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 4096

char *find_most_frequent_word(const char *const words[], size_t count)
{
    size_t i, j;
    size_t max_count = 0;
    size_t max_index = 0;
    int found = 0;
    char *result;
    size_t word_len;
    int written;

    if (words == NULL || count == 0) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        size_t current_count = 0;

        if (words[i] == NULL) {
            continue;
        }

        for (j = 0; j < count; j++) {
            if (words[j] != NULL &&
                strncmp(words[i], words[j], MAX_WORD_LENGTH) == 0) {
                current_count++;
            }
        }

        if (!found || current_count > max_count) {
            max_count = current_count;
            max_index = i;
            found = 1;
        }
    }

    if (!found) {
        return NULL;
    }

    word_len = strnlen(words[max_index], MAX_WORD_LENGTH);
    if (word_len == MAX_WORD_LENGTH) {
        return NULL;
    }

    result = malloc(word_len + 1);
    if (result == NULL) {
        return NULL;
    }

    written = snprintf(result, word_len + 1, "%s", words[max_index]);
    if (written < 0 || (size_t)written > word_len) {
        free(result);
        return NULL;
    }

    return result;
}

int main(void)
{
    const char *words[] = {
        "apple", "banana", "apple", "cherry",
        "banana", "apple", "cherry", "banana"
    };
    size_t count = sizeof(words) / sizeof(words[0]);
    char *most_frequent;

    most_frequent = find_most_frequent_word(words, count);
    if (most_frequent == NULL) {
        fprintf(stderr, "Error: unable to determine the most frequent word\n");
        return EXIT_FAILURE;
    }

    printf("Most frequent word: %s\n", most_frequent);

    free(most_frequent);

    return EXIT_SUCCESS;
}