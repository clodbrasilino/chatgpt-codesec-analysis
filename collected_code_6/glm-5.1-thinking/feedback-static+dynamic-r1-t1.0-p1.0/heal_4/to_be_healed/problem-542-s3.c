#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char *replace_with_colon(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == SIZE_MAX) {
        regfree(&regex);
        return NULL;
    }

    char *result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t res_idx = 0;
    const char *start = str;
    regmatch_t pmatch[1];

    while (1) {
        if (start >= str + len) {
            result[res_idx] = '\0';
            break;
        }

        ret = regexec(&regex, start, 1, pmatch, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = len - (size_t)(start - str);
            size_t available = len - res_idx;
            size_t copy_len = remaining < available ? remaining : available;
            if (copy_len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + res_idx, start, copy_len);
                res_idx += copy_len;
            }
            result[res_idx] = '\0';
            break;
        }

        if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        size_t match_start = (size_t)pmatch[0].rm_so;
        size_t match_end = (size_t)pmatch[0].rm_eo;

        if (match_start > 0) {
            size_t available = len - res_idx;
            size_t copy_len = match_start < available ? match_start : available;
            if (copy_len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + res_idx, start, copy_len);
                res_idx += copy_len;
            }
        }

        if (res_idx < len) {
            result[res_idx++] = ':';
        }

        if (match_end > 0) {
            start += match_end;
        } else {
            start++;
        }
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *input = "Hello world, this.is a test.";
    char *output = replace_with_colon(input);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    return 0;
}