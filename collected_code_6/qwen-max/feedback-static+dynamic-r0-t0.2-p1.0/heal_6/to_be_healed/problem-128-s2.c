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

    char **result = (char **)malloc(*filtered_count * sizeof(char *));
    if (result == NULL) return NULL;

    int index = 0;
    for (int i = 0; i < word_count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (words[i] && strlen(words[i]) > n) {
            size_t len = strnlen(words[i], 1024);
            result[index] = (char *)malloc((len + 1) * sizeof(char));
            if (result[index] == NULL) {
                while (index > 0) {
                    free(result[--index]);
                }
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(result[index], words[i], len + 1);
            result[index][len] = '\0';
            index++;
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
    }

    return 0;
}