#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *first_repeated_word(const char *str)
{
    char **seen = NULL;
    size_t count = 0;
    const char *p = str;

    if (str == NULL) {
        return NULL;
    }

    while (*p != '\0') {
        while (*p != '\0' && isspace((unsigned char)*p)) {
            ++p;
        }
        if (*p == '\0') {
            break;
        }

        const char *start = p;
        while (*p != '\0' && !isspace((unsigned char)*p)) {
            ++p;
        }
        size_t len = p - start;

        char *word = malloc(len + 1);
        if (word == NULL) {
            for (size_t i = 0; i < count; ++i) {
                free(seen[i]);
            }
            free(seen);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(word, start, len);
        word[len] = '\0';

        for (size_t i = 0; i < count; ++i) {
            if (strcmp(seen[i], word) == 0) {
                char *result = seen[i];
                for (size_t j = 0; j < count; ++j) {
                    if (j != i) {
                        free(seen[j]);
                    }
                }
                free(seen);
                free(word);
                return result;
            }
        }

        char **tmp = realloc(seen, (count + 1) * sizeof(*seen));
        if (tmp == NULL) {
            free(word);
            for (size_t i = 0; i < count; ++i) {
                free(seen[i]);
            }
            free(seen);
            return NULL;
        }
        seen = tmp;
        seen[count] = word;
        ++count;
    }

    for (size_t i = 0; i < count; ++i) {
        free(seen[i]);
    }
    free(seen);

    const char *none_str = "None";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t none_len = strlen(none_str);
    char *none = malloc(none_len + 1);
    if (none != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(none, none_str);
    }
    return none;
}

int main(void)
{
    /* Possible weaknesses found:
     *  Variable 'text' can be declared as const array [constVariable]
     */
    char text[] = "apple banana apple orange banana";
    char *word = first_repeated_word(text);
    if (word != NULL) {
        printf("%s\n", word);
        free(word);
    } else {
        printf("None\n");
    }
    return 0;
}