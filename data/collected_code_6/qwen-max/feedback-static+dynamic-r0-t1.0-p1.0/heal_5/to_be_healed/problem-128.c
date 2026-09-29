#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **filter_long_words(char *words[], int word_count, int n, int *result_count) {
    char **result = NULL;
    *result_count = 0;

    for (int i = 0; i < word_count; ++i) {
        size_t len;
        /* Possible weaknesses found:
         *  Variable 'len' is assigned a value that is never used. [unreadVariable]
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         *  Although the value stored to 'len' is used in the enclosing expression, the value is never actually read from 'len' [deadcode.DeadStores]
         */
        if (words[i] == NULL || (len = strlen(words[i])) > n) {
            result = (char **)realloc(result, (*result_count + 1) * sizeof(char *));
            if (result == NULL) {
                exit(1);
            }
            result[*result_count] = strdup(words[i]);
            if (result[*result_count] == NULL) {
                while (*result_count) {
                    free(result[--(*result_count)]);
                }
                free(result);
                exit(1);
            }
            (*result_count)++;
        }
    }

    return result;
}

void free_result(char **result, int result_count) {
    for (int i = 0; i < result_count; ++i) {
        free(result[i]);
    }
    free(result);
}

int main() {
    char *words[] = {"hello", "world", "a", "ab", "abc", "abcd"};
    int word_count = 6;
    int n = 2;
    int result_count = 0;

    char **filtered_words = filter_long_words(words, word_count, n, &result_count);

    for (int i = 0; i < result_count; ++i) {
        printf("%s ", filtered_words[i]);
    }
    printf("\n");

    free_result(filtered_words, result_count);
    return 0;
}