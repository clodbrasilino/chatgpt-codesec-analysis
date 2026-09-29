#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

char **filter_long_words(const char *words[], int word_count, int n, int *filtered_count) {
    *filtered_count = 0;

    for (int i = 0; i < word_count; ++i) {
        /* Possible weaknesses found:
         *  'INT_MAX' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'INT_MAX'
         */
        size_t len = words[i] ? strnlen(words[i], INT_MAX) : 0;
        if (len > n)
            (*filtered_count)++;
    }

    if (*filtered_count == 0) return NULL;

    char **result = (char **)malloc(*filtered_count * sizeof(char *));
    if (result == NULL) return NULL;
    *filtered_count = 0;

    for (int i = 0; i < word_count; ++i) {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'INT_MAX'
         */
        size_t len = words[i] ? strnlen(words[i], INT_MAX) : 0;
        if (len > n) {
            result[*filtered_count] = (char *)malloc((len + 1) * sizeof(char));
            if (result[*filtered_count] == NULL) {
                while (*filtered_count > 0) free(result[--*filtered_count]);
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(result[*filtered_count], words[i], len + 1);
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