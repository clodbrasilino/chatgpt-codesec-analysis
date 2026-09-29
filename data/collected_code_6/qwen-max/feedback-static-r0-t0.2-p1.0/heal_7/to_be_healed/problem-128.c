#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **filter_long_words(char *words[], int word_count, int n, int *filtered_count) {
    *filtered_count = 0;
    for (int i = 0; i < word_count; ++i) {
        size_t len = 0;
        /* Possible weaknesses found:
         *  Redundant condition: If 'words[i][len] != '\0'', the comparison 'words[i][len] != 0' is always true. [redundantCondition]
         */
        while (words[i][len] != '\0' && words[i][len] != 0) {
            len++;
            if (len > n) {
                (*filtered_count)++;
                break;
            }
        }
    }

    char **result = (char **)malloc(*filtered_count * sizeof(char *));
    if (result == NULL) return NULL;

    *filtered_count = 0;
    for (int i = 0; i < word_count; ++i) {
        size_t len = 0;
        /* Possible weaknesses found:
         *  Redundant condition: If 'words[i][len] != '\0'', the comparison 'words[i][len] != 0' is always true. [redundantCondition]
         */
        while (words[i][len] != '\0' && words[i][len] != 0) {
            len++;
            if (len > n) {
                result[*filtered_count] = words[i];
                (*filtered_count)++;
                break;
            }
        }
    }

    return result;
}

int main() {
    char *words[] = {"hello", "world", "a", "ab", "abc", "abcd"};
    int word_count = 6;
    int n = 2;
    int filtered_count;

    char **filtered_words = filter_long_words(words, word_count, n, &filtered_count);

    if (filtered_words != NULL) {
        for (int i = 0; i < filtered_count; ++i) {
            printf("%s\n", filtered_words[i]);
        }
        free(filtered_words);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}