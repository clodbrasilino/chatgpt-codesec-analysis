#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    result = malloc(len + 1);
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

        if (match.rm_so == -1) {
            break;
        }

        size_t match_len = match.rm_eo - match.rm_so;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + result_idx, str + offset + match.rm_so, match_len);
        result_idx += match_len;

        offset += match.rm_eo;
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