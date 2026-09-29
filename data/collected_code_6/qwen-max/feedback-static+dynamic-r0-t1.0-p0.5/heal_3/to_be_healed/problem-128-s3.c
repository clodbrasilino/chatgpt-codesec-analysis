#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **filter_long_words(char *words[], int word_count, int n, int *filtered_count) {
    *filtered_count = 0;

    for (int i = 0; i < word_count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(words[i]) > n) {
            (*filtered_count)++;
        }
    }

    char **result = (char **)malloc(*filtered_count * sizeof(char *));
    if (result == NULL) return NULL;
    *filtered_count = 0;

    for (int i = 0; i < word_count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(words[i]) > n) {
            result[*filtered_count] = words[i];
            (*filtered_count)++;
        }
    }

    return result;
}

int main() {
    char *words[] = {"hello", "world", "a", "of", "programming"};
    int word_count = 5;
    int n = 3;
    int filtered_count;

    char **filtered_words = filter_long_words(words, word_count, n, &filtered_count);

    if (filtered_words != NULL) {
        for (int i = 0; i < filtered_count; ++i) {
            printf("%s\n", filtered_words[i]);
        }
        free(filtered_words);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
    }

    return 0;
}