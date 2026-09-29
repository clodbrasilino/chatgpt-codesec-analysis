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

    char** shortlisted = malloc(num_words * sizeof(char*));
    if (shortlisted == NULL) {
        *out_count = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < num_words; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (words[i] != NULL && strlen(words[i]) > (size_t)n) {
            shortlisted[count] = strdup(words[i]);
            if (shortlisted[count] == NULL) {
                for (int j = 0; j < count; j++) {
                    free(shortlisted[j]);
                }
                free(shortlisted);
                *out_count = 0;
                return NULL;
            }
            count++;
        }
    }

    *out_count = count;
    
    if (count == 0) {
        free(shortlisted);
        return NULL;
    }

    char** resized = realloc(shortlisted, count * sizeof(char*));
    if (resized != NULL) {
        shortlisted = resized;
    }

    return shortlisted;
}

int main(void) {
    char* words[] = {"apple", "cat", "banana", "dog", "elephant", "fox"};
    int num_words = sizeof(words) / sizeof(words[0]);
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