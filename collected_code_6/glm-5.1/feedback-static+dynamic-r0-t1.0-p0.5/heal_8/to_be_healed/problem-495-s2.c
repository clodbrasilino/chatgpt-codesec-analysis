#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* remove_lowercase_substrings(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
    char* result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_idx = 0;
    const char* current = str;

    regmatch_t match;

    while (1) {
        ret = regexec(&regex, current, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = strnlen(current, len - (current - str));
            if (result_idx + remaining <= len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_idx, current, remaining);
            }
            result_idx += remaining;
            break;
        }

        if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        size_t prefix_len = match.rm_so;
        if (result_idx + prefix_len <= len) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_idx, current, prefix_len);
        } else {
            prefix_len = len - result_idx;
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_idx, current, prefix_len);
        }
        result_idx += prefix_len;

        current += match.rm_eo;
    }

    if (result_idx <= len) {
        result[result_idx] = '\0';
    } else {
        result[len] = '\0';
    }

    char* final_result = realloc(result, result_idx + 1);
    if (final_result == NULL) {
        free(result);
        regfree(&regex);
        return NULL;
    }

    regfree(&regex);

    return final_result;
}

int main() {
    const char* input = "Hello World abc DEF 123 xyz";
    char* output = remove_lowercase_substrings(input);

    if (output != NULL) {
        printf("Original: %s\n", input);
        printf("Modified: %s\n", output);
        free(output);
    }

    return 0;
}