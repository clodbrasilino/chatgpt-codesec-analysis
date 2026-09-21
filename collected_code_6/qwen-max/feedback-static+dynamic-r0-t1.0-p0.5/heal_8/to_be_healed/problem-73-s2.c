#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void split_string(const char *input, const char *delimiters, char ***result, int *count) {
    regex_t re;
    regmatch_t match[1];
    int status, offset = 0, len, i = 0;

    if (regcomp(&re, delimiters, REG_EXTENDED | REG_NEWLINE) != 0) {
        *result = NULL;
        *count = 0;
        return;
    }

    *count = 1;
    /* Possible weaknesses found:
     *  Although the value stored to 'status' is used in the enclosing expression, the value is never actually read from 'status' [deadcode.DeadStores]
     */
    while ((status = regexec(&re, input + offset, 1, match, 0)) == 0) {
        (*count)++;
        offset += match[0].rm_eo;
    }
    *result = (char **)calloc(*count, sizeof(char *));
    if (*result == NULL) {
        regfree(&re);
        *count = 0;
        return;
    }

    offset = 0;
    i = 0;
    while (i < *count - 1) {
        len = match[0].rm_so - offset;
        (*result)[i] = (char *)malloc(len + 1);
        if ((*result)[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free((*result)[j]);
            }
            free(*result);
            regfree(&re);
            *result = NULL;
            *count = 0;
            return;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy((*result)[i], input + offset, len);
        (*result)[i][len] = '\0';
        offset += match[0].rm_eo;
        i++;
        if (regexec(&re, input + offset, 1, match, 0) != 0) {
            break;
        }
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = (int)strnlen(input + offset, (strlen(input) + 1 - offset));
    (*result)[i] = (char *)malloc(len + 1);
    if ((*result)[i] == NULL) {
        for (int j = 0; j < i; j++) {
            free((*result)[j]);
        }
        free(*result);
        regfree(&re);
        *result = NULL;
        *count = 0;
        return;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy((*result)[i], input + offset, len);
    (*result)[i][len] = '\0';

    regfree(&re);
}

int main() {
    const char *input = "apple,orange;banana|grape";
    const char *delimiters = ",;|";
    char **result = NULL;
    int count = 0;

    split_string(input, delimiters, &result, &count);

    for (int i = 0; i < count; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);

    return 0;
}