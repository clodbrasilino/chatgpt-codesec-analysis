#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **shortlist_words(char **words, int word_count, size_t n, int *result_count) {
    char **result = NULL;
    int count = 0;
    int i;

    if (words == NULL || result_count == NULL) {
        return NULL;
    }

    for (i = 0; i < word_count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (words[i] != NULL && strlen(words[i]) > n) {
            count++;
        }
    }

    if (count == 0) {
        *result_count = 0;
        return NULL;
    }

    result = (char **)malloc((size_t)count * sizeof(char *));
    if (result == NULL) {
        *result_count = 0;
        return NULL;
    }

    count = 0;
    for (i = 0; i < word_count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (words[i] != NULL && strlen(words[i]) > n) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            result[count] = (char *)malloc((strlen(words[i]) + 1) * sizeof(char));
            if (result[count] == NULL) {
                int j;
                for (j = 0; j < count; j++) {
                    free(result[j]);
                }
                free(result);
                *result_count = 0;
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
             */
            strcpy(result[count], words[i]);
            count++;
        }
    }

    *result_count = count;
    return result;
}

int main(void) {
    char *words[] = {"apple", "banana", "kiwi", "strawberry", "pear", "grapefruit"};
    int word_count = 6;
    size_t n = 5;
    int result_count = 0;
    char **shortlisted = NULL;
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    int i;

    shortlisted = shortlist_words(words, word_count, n, &result_count);

    if (shortlisted != NULL) {
        printf("Words longer than %zu characters:\n", n);
        for (i = 0; i < result_count; i++) {
            printf("%s\n", shortlisted[i]);
            free(shortlisted[i]);
        }
        free(shortlisted);
    } else {
        printf("No words longer than %zu characters found.\n", n);
    }

    return 0;
}