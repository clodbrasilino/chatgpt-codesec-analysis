#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_STR_LEN 1048576

char *remove_non_alnum(const char *str) {
    regex_t regex;
    int ret;
    char *result;
    size_t len;
    size_t result_idx = 0;
    size_t offset = 0;

    if (str == NULL) {
        return NULL;
    }

    len = strnlen(str, MAX_STR_LEN);
    if (len == MAX_STR_LEN) {
        return NULL;
    }

    size_t result_size = len + 1;
    result = malloc(result_size);
    if (result == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[a-zA-Z0-9]+", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    while (offset < len) {
        regmatch_t match;
        ret = regexec(&regex, str + offset, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }

        /* Possible weaknesses found:
         *  Assuming that condition 'match.rm_eo<=match.rm_so' is not redundant
         */
        if (match.rm_so == -1 || match.rm_eo <= match.rm_so) {
            break;
        }

        /* Possible weaknesses found:
         *  Assignment 'match_len=match.rm_eo-match.rm_so', assigned value is greater than 0
         */
        size_t match_len = match.rm_eo - match.rm_so;
        size_t remaining = result_size - result_idx - 1;
        size_t copy_len = match_len;

        if (copy_len > remaining) {
            copy_len = remaining;
        }

        if (copy_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_idx, str + offset + match.rm_so, copy_len);
            result_idx += copy_len;
        }

        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if (match_len > remaining) {
            break;
        }

        offset += match.rm_eo;
        /* Possible weaknesses found:
         *  Condition 'match_len==0' is always false
         *  Condition 'match_len==0' is always false [knownConditionTrueFalse]
         */
        if (match_len == 0) {
            offset++;
        }
    }

    result[result_idx] = '\0';
    regfree(&regex);

    char *trimmed = realloc(result, result_idx + 1);
    if (trimmed != NULL) {
        return trimmed;
    }
    
    return result;
}

int main(void) {
    const char *input = "Hello, World! 123 @#";
    char *output = remove_non_alnum(input);
    
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    
    return 0;
}