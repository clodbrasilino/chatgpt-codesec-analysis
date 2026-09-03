#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shortlist_words(char **words, size_t word_count, size_t n, char ***result, size_t *result_count) {
    if (result == NULL || result_count == NULL) {
        return -1;
    }
    if (word_count > 0 && words == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    size_t count = 0;
    for (size_t i = 0; i < word_count; i++) {
        if (words[i] != NULL && strlen(words[i]) > n) {
            count++;
        }
    }

    if (count == 0) {
        return 0;
    }

    char **shortlisted = malloc(count * sizeof(char *));
    if (shortlisted == NULL) {
        return -1;
    }

    size_t index = 0;
    for (size_t i = 0; i < word_count; i++) {
        if (words[i] != NULL && strlen(words[i]) > n) {
            shortlisted[index++] = words[i];
        }
    }

    *result = shortlisted;
    *result_count = count;
    return 0;
}

int main(void) {
    char *words[] = {"apple", "a", "banana", "cat", "dog", "elephant", "hi"};
    size_t word_count = sizeof(words) / sizeof(words[0]);
    size_t n = 3;
    char **shortlisted = NULL;
    size_t shortlisted_count = 0;

    if (shortlist_words(words, word_count, n, &shortlisted, &shortlisted_count) != 0) {
        fprintf(stderr, "Failed to shortlist words\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < shortlisted_count; i++) {
        printf("%s\n", shortlisted[i]);
    }

    free(shortlisted);
    return EXIT_SUCCESS;
}