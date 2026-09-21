#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

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

    while (1) {
        regmatch_t match;
        ret = regexec(&regex, current, 1, &match, 0);
        
        if (ret == REG_NOMATCH) {
            size_t remaining = strnlen(current, (len + 1) - (current - str));
            size_t buffer_space = (len + 1) - result_idx;
            if (remaining > 0 && remaining <= buffer_space) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_idx, current, remaining);
                result_idx += remaining;
            }
            break;
        }

        if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        size_t prefix_len = match.rm_so;
        if (prefix_len > 0) {
            size_t buffer_space = (len + 1) - result_idx;
            if (prefix_len <= buffer_space) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_idx, current, prefix_len);
                result_idx += prefix_len;
            }
        }

        current += match.rm_eo;
    }

    result[result_idx] = '\0';

    char* final_result = realloc(result, result_idx + 1);
    if (final_result != NULL) {
        result = final_result;
    }

    regfree(&regex);

    return result;
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