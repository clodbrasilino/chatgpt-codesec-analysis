#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_lowercase(const char *str, size_t len) {
    if (str == NULL || len == (size_t)-1) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, "[[:lower:]]+", REG_EXTENDED) != 0) {
        return NULL;
    }

    char *safe_str = malloc(len + 1);
    if (safe_str == NULL) {
        regfree(&regex);
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(safe_str, str, len);
    safe_str[len] = '\0';

    char *result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        free(safe_str);
        return NULL;
    }

    const char *ptr = safe_str;
    char *res_ptr = result;
    size_t res_len = 0;

    while (1) {
        regmatch_t match;
        int ret = regexec(&regex, ptr, 1, &match, 0);
        
        if (ret == REG_NOMATCH) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t remaining_len = strlen(ptr);
            size_t space_left = len - res_len;
            if (remaining_len > space_left) {
                remaining_len = space_left;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(res_ptr, ptr, remaining_len);
            res_ptr += remaining_len;
            break;
        }
        
        if (ret != 0) {
            break;
        }

        if (match.rm_so > 0) {
            size_t copy_len = match.rm_so;
            size_t space_left = len - res_len;
            if (copy_len > space_left) {
                copy_len = space_left;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(res_ptr, ptr, copy_len);
            res_ptr += copy_len;
            res_len += copy_len;
        }

        ptr += match.rm_eo;

        if (match.rm_so == match.rm_eo) {
            if (*ptr != '\0') {
                if (res_len < len) {
                    *res_ptr++ = *ptr++;
                    res_len++;
                } else {
                    ptr++;
                }
            } else {
                break;
            }
        }
    }

    *res_ptr = '\0';
    regfree(&regex);
    free(safe_str);
    return result;
}

int main(void) {
    const char input[] = "HelloWorld123abcXYZ";
    char *result = remove_lowercase(input, sizeof(input) - 1);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }
    return 0;
}