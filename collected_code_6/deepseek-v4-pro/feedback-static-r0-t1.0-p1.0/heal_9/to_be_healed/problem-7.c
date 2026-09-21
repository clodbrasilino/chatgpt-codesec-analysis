#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

int find_words(const char *text, char ***words, size_t *count) {
    regex_t regex;
    regmatch_t match;
    const char *p;
    int ret;
    size_t capacity = 10;
    char **result;
    size_t i;

    *count = 0;
    *words = NULL;

    if (!text) {
        return -1;
    }

    ret = regcomp(&regex, "[a-zA-Z]{4,}", REG_EXTENDED);
    if (ret) {
        return -1;
    }

    result = malloc(capacity * sizeof(char *));
    if (!result) {
        regfree(&regex);
        return -1;
    }

    p = text;

    while (regexec(&regex, p, 1, &match, 0) == 0) {
        size_t length;
        size_t remaining;

        if (match.rm_so < 0 || match.rm_eo < 0 || match.rm_so >= match.rm_eo) {
            for (i = 0; i < *count; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            return -1;
        }

        length = (size_t)(match.rm_eo - match.rm_so);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        remaining = strlen(p);

        if (match.rm_so > remaining || length > remaining ||
            (size_t)match.rm_so > remaining - length) {
            for (i = 0; i < *count; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            return -1;
        }

        if (*count >= capacity) {
            char **temp;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                for (i = 0; i < *count; i++) {
                    free(result[i]);
                }
                free(result);
                regfree(&regex);
                return -1;
            }

            new_capacity = capacity * 2;

            temp = realloc(result, new_capacity * sizeof(char *));
            if (!temp) {
                for (i = 0; i < *count; i++) {
                    free(result[i]);
                }
                free(result);
                regfree(&regex);
                return -1;
            }
            result = temp;
            capacity = new_capacity;
        }

        result[*count] = malloc(length + 1);
        if (!result[*count]) {
            for (i = 0; i < *count; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[*count], p + match.rm_so, length);
        result[*count][length] = '\0';
        (*count)++;
        p += match.rm_eo;
    }

    regfree(&regex);
    *words = result;
    return 0;
}

int main(void) {
    const char *text = "This is a test string with several words like apple banana cat dog elephant";
    char **words;
    size_t count;
    size_t i;
    int ret;

    ret = find_words(text, &words, &count);
    if (ret != 0) {
        fprintf(stderr, "Error finding words\n");
        return 1;
    }

    for (i = 0; i < count; i++) {
        printf("%s\n", words[i]);
        free(words[i]);
    }
    free(words);

    return 0;
}