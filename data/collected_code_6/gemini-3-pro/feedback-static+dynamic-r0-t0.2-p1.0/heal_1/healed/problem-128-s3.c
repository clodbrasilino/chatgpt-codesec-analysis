#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** shortlist_words(char** words, int num_words, int n, int* out_count) {
    if (words == NULL || out_count == NULL || num_words <= 0) {
        if (out_count != NULL) {
            *out_count = 0;
        }
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < num_words; i++) {
        if (words[i] != NULL && strnlen(words[i], n + 1) > (size_t)n) {
            count++;
        }
    }

    if (count == 0) {
        *out_count = 0;
        return NULL;
    }

    char** shortlisted = (char**)malloc(count * sizeof(char*));
    if (shortlisted == NULL) {
        *out_count = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < num_words; i++) {
        if (words[i] != NULL && strnlen(words[i], n + 1) > (size_t)n) {
            shortlisted[index] = strdup(words[i]);
            if (shortlisted[index] == NULL) {
                for (int j = 0; j < index; j++) {
                    free(shortlisted[j]);
                }
                free(shortlisted);
                *out_count = 0;
                return NULL;
            }
            index++;
        }
    }

    *out_count = count;
    return shortlisted;
}

int main(void) {
    char* words[] = {"apple", "cat", "banana", "dog", "elephant", "fox"};
    int num_words = 6;
    int n = 4;
    int out_count = 0;

    char** result = shortlist_words(words, num_words, n, &out_count);

    if (result != NULL) {
        for (int i = 0; i < out_count; i++) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    }

    return 0;
}