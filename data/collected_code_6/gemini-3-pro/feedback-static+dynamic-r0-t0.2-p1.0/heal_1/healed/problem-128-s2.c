#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** shortlist_words(char** words, int num_words, int n, int* out_count) {
    if (words == NULL || out_count == NULL || num_words < 0 || n < 0) {
        if (out_count != NULL) {
            *out_count = 0;
        }
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < num_words; i++) {
        if (words[i] != NULL) {
            size_t len = 0;
            while (len <= (size_t)n && words[i][len] != '\0') {
                len++;
            }
            if (len > (size_t)n) {
                count++;
            }
        }
    }

    char** shortlisted = (char**)malloc(count * sizeof(char*));
    if (shortlisted == NULL) {
        *out_count = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < num_words; i++) {
        if (words[i] != NULL) {
            size_t len = 0;
            while (len <= (size_t)n && words[i][len] != '\0') {
                len++;
            }
            if (len > (size_t)n) {
                size_t actual_len = 0;
                while (words[i][actual_len] != '\0') {
                    actual_len++;
                }
                
                shortlisted[index] = (char*)malloc(actual_len + 1);
                if (shortlisted[index] == NULL) {
                    for (int j = 0; j < index; j++) {
                        free(shortlisted[j]);
                    }
                    free(shortlisted);
                    *out_count = 0;
                    return NULL;
                }
                
                for (size_t j = 0; j <= actual_len; j++) {
                    shortlisted[index][j] = words[i][j];
                }
                index++;
            }
        }
    }

    *out_count = count;
    return shortlisted;
}

int main(void) {
    char* words[] = {"apple", "cat", "banana", "dog", "elephant", "fox"};
    int num_words = 6;
    int n = 3;
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