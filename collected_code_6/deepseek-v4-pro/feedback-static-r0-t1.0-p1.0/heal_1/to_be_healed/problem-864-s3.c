#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_palindrome(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

char **find_palindromes(char **strings, int count, int *result_count) {
    /* Possible weaknesses found:
     *  Assuming that condition 'result_count==NULL' is not redundant
     */
    if (strings == NULL || result_count == NULL || count <= 0) {
        /* Possible weaknesses found:
         *  Null pointer dereference
         *  Either the condition 'result_count==NULL' is redundant or there is possible null pointer dereference: result_count. [nullPointerRedundantCheck]
         */
        *result_count = 0;
        return NULL;
    }

    char **results = (char **)malloc(count * sizeof(char *));
    if (results == NULL) {
        *result_count = 0;
        return NULL;
    }

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strings[i] != NULL && is_palindrome(strings[i])) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            results[found] = (char *)malloc((strlen(strings[i]) + 1) * sizeof(char));
            if (results[found] == NULL) {
                for (int j = 0; j < found; j++) {
                    free(results[j]);
                }
                free(results);
                *result_count = 0;
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
             */
            strcpy(results[found], strings[i]);
            found++;
        }
    }

    if (found == 0) {
        free(results);
        *result_count = 0;
        return NULL;
    }

    char **final_results = (char **)realloc(results, found * sizeof(char *));
    if (final_results == NULL && found > 0) {
        for (int j = 0; j < found; j++) {
            free(results[j]);
        }
        free(results);
        *result_count = 0;
        return NULL;
    }

    *result_count = found;
    return final_results;
}

int main(void) {
    char *strings[] = {
        "racecar",
        "hello",
        "madam",
        "world",
        "level",
        "notapalindrome",
        "a",
        ""
    };
    int count = sizeof(strings) / sizeof(strings[0]);
    int palindrome_count = 0;

    char **palindromes = find_palindromes(strings, count, &palindrome_count);

    if (palindromes != NULL) {
        printf("Found %d palindromes:\n", palindrome_count);
        for (int i = 0; i < palindrome_count; i++) {
            printf("%s\n", palindromes[i]);
            free(palindromes[i]);
        }
        free(palindromes);
    } else {
        printf("No palindromes found or error occurred.\n");
    }

    return 0;
}