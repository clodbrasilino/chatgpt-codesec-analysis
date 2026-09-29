#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **shortlist_words(char **words, int word_count, int n, int *result_count) {
    char **result = NULL;
    int count = 0;
    int i;

    if (words == NULL || result_count == NULL || n < 0) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    for (i = 0; i < word_count; i++) {
        if (words[i] != NULL && (int)strlen(words[i]) > n) {
            count++;
        }
    }

    if (count == 0) {
        *result_count = 0;
        return NULL;
    }

    result = (char **)malloc((size_t)count * sizeof(char *));
    if (result == NULL) {
        *result_count = 0;
        return NULL;
    }

    count = 0;
    for (i = 0; i < word_count; i++) {
        if (words[i] != NULL && (int)strlen(words[i]) > n) {
            result[count] = words[i];
            count++;
        }
    }

    *result_count = count;
    return result;
}

int main(void) {
    char *words[] = {"apple", "banana", "kiwi", "strawberry", "fig", "grapefruit"};
    int word_count = 6;
    int n = 5;
    int result_count = 0;
    char **shortlisted = NULL;
    int i;

    shortlisted = shortlist_words(words, word_count, n, &result_count);

    if (shortlisted != NULL) {
        for (i = 0; i < result_count; i++) {
            printf("%s\n", shortlisted[i]);
        }
        free(shortlisted);
    } else {
        printf("No words longer than %d characters found.\n", n);
    }

    return 0;
}