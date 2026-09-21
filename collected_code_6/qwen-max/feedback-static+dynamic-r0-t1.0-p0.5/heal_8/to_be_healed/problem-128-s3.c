#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **filter_long_words(const char *words[], int word_count, int n, int *filtered_count) {
    *filtered_count = 0;

    for (int i = 0; i < word_count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (words[i] && strlen(words[i]) > n) {
            (*filtered_count)++;
        }
    }

    if (*filtered_count == 0) return NULL;

    char **result = (char **)malloc(*filtered_count * sizeof(char *));
    if (result == NULL) return NULL;
    *filtered_count = 0;

    for (int i = 0; i < word_count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (words[i] && (strlen(words[i]) > n)) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(words[i]);
            result[*filtered_count] = (char *)malloc((len + 1) * sizeof(char));
            if (result[*filtered_count] == NULL) {
                while (*filtered_count > 0) free(result[--*filtered_count]);
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[*filtered_count], words[i], len + 1);
            (*filtered_count)++;
        }
    }

    return result;
}

int main() {
    const char *words[] = {"hello", "world", "a", "of", "programming"};
    int word_count = 5;
    int n = 3;
    int filtered_count;

    char **filtered_words = filter_long_words(words, word_count, n, &filtered_count);

    if (filtered_words != NULL) {
        for (int i = 0; i < filtered_count; ++i) {
            printf("%s\n", filtered_words[i]);
            free(filtered_words[i]);
        }
        free(filtered_words);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
    }

    return 0;
}