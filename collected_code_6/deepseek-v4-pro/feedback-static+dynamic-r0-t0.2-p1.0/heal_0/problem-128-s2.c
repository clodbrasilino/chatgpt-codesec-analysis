#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **shortlist_words(char **words, int word_count, size_t n, int *result_count) {
    char **result = NULL;
    int count = 0;
    int i;

    if (words == NULL || result_count == NULL) {
        return NULL;
    }

    for (i = 0; i < word_count; i++) {
        if (words[i] != NULL && strlen(words[i]) > n) {
            count++;
        }
    }

    result = (char **)malloc((size_t)count * sizeof(char *));
    if (result == NULL && count > 0) {
        *result_count = 0;
        return NULL;
    }

    count = 0;
    for (i = 0; i < word_count; i++) {
        if (words[i] != NULL && strlen(words[i]) > n) {
            result[count] = (char *)malloc((strlen(words[i]) + 1) * sizeof(char));
            if (result[count] == NULL) {
                int j;
                for (j = 0; j < count; j++) {
                    free(result[j]);
                }
                free(result);
                *result_count = 0;
                return NULL;
            }
            strcpy(result[count], words[i]);
            count++;
        }
    }

    *result_count = count;
    return result;
}

void free_shortlisted_words(char **words, int count) {
    int i;
    if (words == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

int main(void) {
    char *word_list[] = {"apple", "banana", "kiwi", "strawberry", "pear", "grapefruit"};
    int word_count = sizeof(word_list) / sizeof(word_list[0]);
    size_t threshold = 5;
    int result_count = 0;
    char **shortlisted = NULL;
    int i;

    shortlisted = shortlist_words(word_list, word_count, threshold, &result_count);

    if (shortlisted == NULL && result_count > 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Words longer than %zu characters:\n", threshold);
    for (i = 0; i < result_count; i++) {
        printf("%s\n", shortlisted[i]);
    }

    free_shortlisted_words(shortlisted, result_count);

    return EXIT_SUCCESS;
}