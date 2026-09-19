#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char **shortlist_words(const char *words[], size_t word_count, size_t n, size_t *out_count)
{
    size_t matches = 0;
    const char **result;

    if (out_count == NULL) {
        return NULL;
    }

    if (words == NULL && word_count > 0) {
        *out_count = 0;
        return NULL;
    }

    for (size_t i = 0; i < word_count; i++) {
        if (words[i] != NULL && strlen(words[i]) > n) {
            matches++;
        }
    }

    if (matches == 0) {
        *out_count = 0;
        return NULL;
    }

    result = malloc(matches * sizeof(*result));
    if (result == NULL) {
        *out_count = matches;
        return NULL;
    }

    matches = 0;
    for (size_t i = 0; i < word_count; i++) {
        if (words[i] != NULL && strlen(words[i]) > n) {
            result[matches] = words[i];
            matches++;
        }
    }

    *out_count = matches;
    return result;
}

int main(void)
{
    const char *words[] = { "apple", "banana", "kiwi", "pear", "grapefruit" };
    size_t word_count = sizeof(words) / sizeof(words[0]);
    size_t min_length = 5;
    size_t selected_count = 0;
    const char **selected;

    selected = shortlist_words(words, word_count, min_length, &selected_count);

    if (selected != NULL) {
        for (size_t i = 0; i < selected_count; i++) {
            printf("%s\n", selected[i]);
        }
        free(selected);
    } else if (selected_count > 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}