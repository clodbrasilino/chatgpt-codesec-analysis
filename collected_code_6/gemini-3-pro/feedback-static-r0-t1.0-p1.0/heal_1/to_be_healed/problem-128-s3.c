#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** shortlist_words(char** words, int num_words, int n, int* returned_count) {
    if (words == NULL || returned_count == NULL || num_words <= 0 || n < 0) {
        if (returned_count != NULL) {
            *returned_count = 0;
        }
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < num_words; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (words[i] != NULL && strlen(words[i]) > (size_t)n) {
            count++;
        }
    }

    char** result = (char**)malloc(count * sizeof(char*));
    if (result == NULL) {
        *returned_count = 0;
        return NULL;
    }

    int idx = 0;
    for (int i = 0; i < num_words; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (words[i] != NULL && strlen(words[i]) > (size_t)n) {
            result[idx] = strdup(words[i]);
            if (result[idx] == NULL) {
                for (int j = 0; j < idx; j++) {
                    free(result[j]);
                }
                free(result);
                *returned_count = 0;
                return NULL;
            }
            idx++;
        }
    }

    *returned_count = count;
    return result;
}

int main(void) {
    char* words[] = {"apple", "cat", "banana", "dog", "elephant"};
    int num_words = 5;
    int n = 4;
    int returned_count = 0;

    char** result = shortlist_words(words, num_words, n, &returned_count);

    if (result != NULL) {
        for (int i = 0; i < returned_count; i++) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    }

    return 0;
}