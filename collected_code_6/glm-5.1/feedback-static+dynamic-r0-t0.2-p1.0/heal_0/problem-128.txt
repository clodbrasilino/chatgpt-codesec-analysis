#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **shortlist_words(char **words, int count, int n, int *result_count) {
    if (words == NULL || count <= 0 || result_count == NULL) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    char **buffer = (char **)malloc(count * sizeof(char *));
    if (buffer == NULL) {
        *result_count = 0;
        return NULL;
    }

    int out_idx = 0;
    for (int i = 0; i < count; i++) {
        if (words[i] != NULL && strlen(words[i]) > n) {
            buffer[out_idx] = words[i];
            out_idx++;
        }
    }

    if (out_idx == 0) {
        free(buffer);
        *result_count = 0;
        return NULL;
    }

    char **result = (char **)realloc(buffer, out_idx * sizeof(char *));
    if (result == NULL) {
        *result_count = out_idx;
        return buffer;
    }

    *result_count = out_idx;
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