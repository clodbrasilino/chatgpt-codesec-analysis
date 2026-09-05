#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **shortlist_words(char **words, int count, int n, int *result_count) {
    if (words == NULL || result_count == NULL || count < 0 || n < 0) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    char **result = malloc(count * sizeof(char *));
    if (result == NULL) {
        *result_count = 0;
        return NULL;
    }

    int out_count = 0;
    for (int i = 0; i < count; i++) {
        if (words[i] != NULL && strlen(words[i]) > n) {
            result[out_count] = words[i];
            out_count++;
        }
    }

    if (out_count == 0) {
        free(result);
        *result_count = 0;
        return NULL;
    }

    char **trimmed_result = realloc(result, out_count * sizeof(char *));
    if (trimmed_result != NULL) {
        result = trimmed_result;
    }

    *result_count = out_count;
    return result;
}

int main(void) {
    char *words[] = {"apple", "banana", "kiwi", "strawberry", "fig", "grapefruit"};
    int count = sizeof(words) / sizeof(words[0]);
    int n = 5;
    int result_count = 0;

    char **shortlisted = shortlist_words(words, count, n, &result_count);

    if (shortlisted != NULL) {
        for (int i = 0; i < result_count; i++) {
            printf("%s\n", shortlisted[i]);
        }
        free(shortlisted);
    }

    return 0;
}