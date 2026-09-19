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
        if (words[i] != NULL && strlen(words[i]) > n) {
            result[count] = words[i];
            count++;
        }
    }

    *result_count = count;
    return result;
}

int main(void) {
    char *words[] = {"apple", "banana", "kiwi", "strawberry", "pear", "grapefruit"};
    int word_count = sizeof(words) / sizeof(words[0]);
    size_t threshold = 5;
    int result_count = 0;
    char **shortlisted = NULL;
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    int i;

    shortlisted = shortlist_words(words, word_count, threshold, &result_count);

    if (shortlisted != NULL) {
        printf("Words longer than %zu characters:\n", threshold);
        for (i = 0; i < result_count; i++) {
            printf("%s\n", shortlisted[i]);
        }
        free(shortlisted);
    } else {
        printf("No words longer than %zu characters found.\n", threshold);
    }

    return 0;
}