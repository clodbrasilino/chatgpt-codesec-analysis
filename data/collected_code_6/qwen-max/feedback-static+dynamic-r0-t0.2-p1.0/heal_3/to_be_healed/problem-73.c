#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

char **split_string(const char *input, const char *delimiters, int *count) {
    regex_t regex;
    regmatch_t matches[1];
    char *str = strdup(input);
    if (str == NULL) {
        return NULL;
    }

    if (regcomp(&regex, delimiters, REG_EXTENDED | REG_NEWLINE) != 0) {
        free(str);
        return NULL;
    }

    *count = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    int offset = 0;
    int nmatch = 1;

    while (regexec(&regex, str + offset, nmatch, matches, 0) == 0) {
        if (matches[0].rm_so > 0) {
            (*count)++;
        }
        offset += matches[0].rm_eo;
    }
    if (offset < len) {
        (*count)++;
    }

    char **result = (char **)malloc((*count + 1) * sizeof(char *));
    if (result == NULL) {
        regfree(&regex);
        free(str);
        return NULL;
    }

    *count = 0;
    offset = 0;

    while (regexec(&regex, str + offset, nmatch, matches, 0) == 0) {
        if (matches[0].rm_so > 0) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            result[*count] = (char *)malloc((matches[0].rm_so + 1) * sizeof(char));
            if (result[*count] == NULL) {
                for (int i = 0; i < *count; i++) {
                    free(result[i]);
                }
                free(result);
                regfree(&regex);
                free(str);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[*count], str + offset, matches[0].rm_so);
            result[*count][matches[0].rm_so] = '\0';
            (*count)++;
        }
        offset += matches[0].rm_eo;
    }
    if (offset < len) {
        result[*count] = (char *)malloc((len - offset + 1) * sizeof(char));
        if (result[*count] == NULL) {
            for (int i = 0; i < *count; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            free(str);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[*count], str + offset, len - offset);
        result[*count][len - offset] = '\0';
        (*count)++;
    }
    result[*count] = NULL;

    regfree(&regex);
    free(str);
    return result;
}

int main() {
    const char *input = "apple,orange;banana|grape";
    const char *delimiters = ",;|";
    int count;
    char **result = split_string(input, delimiters, &count);

    if (result != NULL) {
        for (int i = 0; result[i] != NULL; i++) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    } else {
        fprintf(stderr, "Failed to split string\n");
    }

    return 0;
}