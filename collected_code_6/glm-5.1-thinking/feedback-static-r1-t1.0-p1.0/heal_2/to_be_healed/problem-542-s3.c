#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

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
    char *result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t res_idx = 0;
    const char *start = str;
    const char *end = str + len;
    regmatch_t pmatch[1];

    while (start < end) {
        ret = regexec(&regex, start, 1, pmatch, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = end - start;
            if (res_idx + remaining <= len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + res_idx, start, remaining);
                res_idx += remaining;
            }
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
            if (res_idx + match_start <= len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + res_idx, start, match_start);
                res_idx += match_start;
            }
        }

        if (res_idx <= len) {
            result[res_idx++] = ':';
        }

        start += match_end;
    }

    result[res_idx] = '\0';

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