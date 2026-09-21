#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

char *remove_whitespaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[[:space:]]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t res_idx = 0;
    const char *p = str;
    regmatch_t match;

    while (*p) {
        ret = regexec(&regex, p, 1, &match, 0);
        if (ret == 0) {
            size_t non_space_len = match.rm_so;
            if (non_space_len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + res_idx, p, non_space_len);
                res_idx += non_space_len;
            }
            p += match.rm_eo;
        } else {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t remaining_len = strlen(p);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + res_idx, p, remaining_len);
            res_idx += remaining_len;
            break;
        }
    }

    result[res_idx] = '\0';
    regfree(&regex);
    return result;
}

int main(void) {
    const char *input = " Hello \t World \n from C \r ";
    char *output = remove_whitespaces(input);
    
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    
    return 0;
}